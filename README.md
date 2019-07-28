### 作业要求

	实现一个基于ffmpeg的网络视频播放器，包括以下要求：
	1、平台不限（PC，IOS，Android任选一个）

	2、至少支持flv和m3u8两种格式

	3、健壮性良好

	4、良好使用观看体验

	5、方便快速定位问题

### 项目基本信息
    
    名称：my_player_qt
    音视频解码库：ffmpeg
    界面设计：Qt5
    音频播放：SDL
    视频播放：Qt openGLWidget
    
    开发平台：windows 10 x64
    IDE: Visual Studio 2017
    编译方式：release x64
    
### 目录结构
    1、html: 用doxygen生成的代码结构文件，方便查看源码目录结构，目录结构查看入口为: ./html/annotated.html；

    2、my_player_qt：项目源代码；

    3、我的播放器：打包好的可运行程序，直接双击my_player_qt.exe可以直接运行；
    
    4、my_player_qt.sln：VS解决方案文件；
    
    5、测试流：测试播放器用到的网络流；
	
	6、功能演示.wmv：播放器直接运行版本的基本功能展示视频。

### 播放器功能
**支持播放格式**

    1、本地：mp4, flv, rmvb, flv, avi, mkv, mov, wmv 
    2、网络: flv, m3u8, mp4

**功能**

- [x] 右键菜单打开网络流和本地文件
- [x] 打开和关闭播放列表
- [x] 本地文件直接拖进播放器加入播放列表
- [x] 视频播放和暂停（按键和空格键）
- [x] 进度条拖动跳转
- [x] 快进快退（按键和键盘左右键）
- [x] 音量条调整音量
- [x] 静音和播放（右键菜单和音量图标）
- [x] 鼠标双击进入/退出全屏（ESC退出）
- [x] 窗口尺寸任意调整
- [x] 鼠标定时隐藏，全屏隐藏进度条
- [x] 显示视频详细信息

### 实现细节

	1、创建音频类playerAudio和视频类playerVideo，分别管理音频和视频的解码；

	2、用一个线程类readPacketsThread调用av_read_frame()函数，将得到的音频和视频的packet放入各自的队列；

	3、以音频帧的时间为基准，用playerMediaTimer类管理音视频同步，控制视频帧解码速度同步音频；

	4、因为要控制视频解码速度，所以用frameQueue类保存视频解packet得到的frame，用于playerMediaTimer中读取frame；

	5、创建playerMedia类综合管理音频和视频，给Qt窗体提供音频和视频方法接口；

	6、logger类用于向文件中打印运行时的日志信息，包括自定义日志和ffmpeg的av_log()函数输出的日志；

	7、设置跳出回调函数和超时判断，在网络流加载超时、文件打开超时、打开新视频时跳出av_read_frame()函数阻塞；

	8、播放网络流时，视频packet队列为空时自动暂停，等待队列中数据量达到一定值时播放。

### 源代码编译设置
    
    1、必须安装Qt5；
    2、包含目录要添加源码文件中的include文件夹，库目录添加lib文件夹；
    3、附加依赖项必须添加：Qt5Core.lib Qt5Gui.lib Qt5Widgets.lib Qt5Multimedia.lib avcodec.lib avformat.lib avutil.lib avdevice.lib avfilter.lib postproc.lib swresample.lib swscale.lib SDL2.lib SDL2main.lib SDL2test.lib Wininet.lib。
	