#include "playerAudio.h"
#include "playerMedia.h"
#include "logger.h"

static int audioVolume = 64;

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

playerAudio::playerAudio()
{
	audioContext = nullptr;
	streamIndex = -1;
	stream = nullptr;
	audioClock = 0;
	audioBuff = new uint8_t[BUFFERSIZE];
	audioBuffSize = 0;
	audioBuffIndex = 0;
}

bool playerAudio::audioClose()
{
	if (getAudioQueueSize() > 0)
	{
		SDL_CloseAudio();
		SDL_Quit();
	}
	if (audioBuff)
	{
		delete[] audioBuff;
		audioBuff = nullptr;
	}
	return true;
}

bool playerAudio::audioOpen()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		LOG(LOG_ERROR) << "Could not initialize SDL - " << SDL_GetError() << std::endl;
		return false;
	}
	audioBuff = new uint8_t[BUFFERSIZE];
	audioBuffSize = 0;
	audioBuffIndex = 0;

	SDL_AudioSpec desired;
	desired.freq = audioContext->sample_rate;
	desired.channels = audioContext->channels;
	desired.format = AUDIO_S16SYS;
	desired.samples = audioContext->frame_size;
	desired.silence = 0;
	desired.userdata = audioContext;
	desired.callback = audioCallback;
	if (SDL_OpenAudio(&desired, nullptr) < 0)
	{
		return false;
	}
	SDL_PauseAudio(0);
	return true;
}

void playerAudio::setStreamIndex(const int & streamIndex)
{
	this->streamIndex = streamIndex;
}

int playerAudio::getStreamIndex()
{
	return streamIndex;
}

AVStream * playerAudio::getStream()
{
	return this->stream;
}

void playerAudio::setStream(AVStream *& stream)
{
	this->stream = stream;
}

AVCodecContext * playerAudio::getAVCodecContext()
{
	return audioContext;
}

void playerAudio::setAVCodecContext(AVCodecContext * audioContext)
{
	this->audioContext = audioContext;
}

int playerAudio::getAudioQueueSize()
{
	return audioPackets.getPacketSize();
}

void playerAudio::clearPacket()
{
	this->audioPackets.queueFlush();
}

void playerAudio::enqueuePacket(const AVPacket packet)
{
	audioPackets.enQueue(packet);
}

AVPacket playerAudio::dequeuePacket()
{
	return audioPackets.deQueue();;
}

uint8_t * playerAudio::getAudioBuff()
{
	return audioBuff;
}

void playerAudio::setAudioBuff(uint8_t *& audioBuff)
{
	this->audioBuff = audioBuff;
}

uint32_t playerAudio::getAudioBuffSize()
{
	return audioBuffSize;
}

void playerAudio::setAudioBuffSize(uint32_t audioBuffSize)
{
	this->audioBuffSize = audioBuffSize;
}

uint32_t playerAudio::getAudioBuffIndex()
{
	return audioBuffIndex;
}

void playerAudio::setAudioBuffIndex(uint32_t audioBuffIndex)
{
	this->audioBuffIndex = audioBuffIndex;
}

double playerAudio::getAudioClock()
{
	return audioClock;
}

void playerAudio::setAudioClock(const double & audioClock)
{
	this->audioClock = audioClock;
}

double playerAudio::getCurrentAudioClock()
{
	int hw_buf_size = audioBuffSize - audioBuffIndex;
	int bytes_per_sec = stream->codec->sample_rate * audioContext->channels * 2;
	double pts = audioClock - static_cast<double>(hw_buf_size) / bytes_per_sec;
	return pts;
}

bool playerAudio::getIsPlaying()
{
	return this->isPlay;
}

void playerAudio::setPlaying(bool isPlaying)
{
	this->isPlay = isPlaying;
}

void playerAudio::setVolume(int volume)
{
	audioVolume = volume;
}

playerAudio::~playerAudio()
{
	audioClose();
	if (audioBuff)
	{
		delete[] audioBuff;
		audioBuff = nullptr;
	}
}

int audioDecodeFrame(playerAudio * audio, uint8_t * audioBuffer, int bufferSize)
{
	AVFrame *frameAudio = av_frame_alloc();
	int dataSize = 0;
	AVPacket packet = audio->dequeuePacket();
	
	SwrContext *swrCtx = nullptr;
	static double clock = 0;

	if (packet.size <= 0)
	{
		return -1;
	}

	if (packet.pts != AV_NOPTS_VALUE)
	{
		if (audio->getStream() == nullptr)
			return -1;
		audio->setAudioClock(av_q2d(audio->getStream()->time_base) * packet.pts);
	}
	if (audio->getAVCodecContext() == nullptr)
		return -1;
	
	int ret = avcodec_send_packet(audio->getAVCodecContext(), &packet);
	if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
		return -1;
	ret = avcodec_receive_frame(audio->getAVCodecContext(), frameAudio);
	if (ret < 0 && ret != AVERROR_EOF)
		return -1;

	int pts_audio = (frameAudio->pts * r2d(audio->getStream()->time_base)) * 1000;  
	playerMedia::getInstance()->pts = pts_audio;

	// set channel_layout
	if (frameAudio->channels > 0 && frameAudio->channel_layout == 0)
		frameAudio->channel_layout = av_get_default_channel_layout(frameAudio->channels);
	else if (frameAudio->channels == 0 && frameAudio->channel_layout > 0)
		frameAudio->channels = av_get_channel_layout_nb_channels(frameAudio->channel_layout);

	AVSampleFormat dst_format = AV_SAMPLE_FMT_S16;
	uint64_t dst_layout = av_get_default_channel_layout(frameAudio->channels);
	
	swrCtx = swr_alloc();
	swrCtx = swr_alloc_set_opts(swrCtx, dst_layout, dst_format, frameAudio->sample_rate,
		frameAudio->channel_layout, (AVSampleFormat)frameAudio->format, frameAudio->sample_rate, 0, nullptr);

	if (!swrCtx || swr_init(swrCtx) < 0)
		return -1;

	uint64_t dst_nb_samples = av_rescale_rnd(swr_get_delay(swrCtx, frameAudio->sample_rate) 
		+ frameAudio->nb_samples, frameAudio->sample_rate, frameAudio->sample_rate, AVRounding(1));

	int nb = swr_convert(swrCtx, &audioBuffer, static_cast<int>(dst_nb_samples),
		(const uint8_t**)frameAudio->data, frameAudio->nb_samples);

	//dataSize = frameAudio->channels * nb * av_get_bytes_per_sample(dst_format);
	dataSize = av_samples_get_buffer_size(NULL, frameAudio->channels, nb, dst_format, 1);

	if (audio->getStream()->codec == nullptr)
		return -1;

	audio->setAudioClock(audio->getAudioClock() + static_cast<double>(dataSize) 
		/ (2 * audio->getStream()->codec->channels * audio->getStream()->codec->sample_rate));
	
	av_frame_free(&frameAudio);
	swr_free(&swrCtx);
	return dataSize;
}

void audioCallback(void * userdata, uint8_t * stream, int len)
{
	playerAudio *audio = playerMedia::getInstance()->audio;

	SDL_memset(stream, 0, len);

	int audio_size = 0;
	int len1 = 0;
	while (len > 0)
	{
		if (audio->getAudioBuffIndex() >= audio->getAudioBuffSize()) 
		{
			audio_size = audioDecodeFrame(audio, audio->getAudioBuff(), sizeof(audio->getAudioBuff()));
			if (audio_size < 0) 
			{
				audio->setAudioBuffSize(0);
				memset(audio->getAudioBuff(), 0, audio->getAudioBuffSize());
			}
			else
				audio->setAudioBuffSize(audio_size);

			audio->setAudioBuffIndex(0);
		}
		// 缓冲区中剩下的数据长度
		len1 = audio->getAudioBuffSize() - audio->getAudioBuffIndex(); 
		if (len1 > len) 
			len1 = len;

		SDL_MixAudio(stream, audio->getAudioBuff() + audio->getAudioBuffIndex(), len, audioVolume);

		len -= len1;
		stream += len1;
		audio->setAudioBuffIndex(audio->getAudioBuffIndex() + len1);
	}
}
