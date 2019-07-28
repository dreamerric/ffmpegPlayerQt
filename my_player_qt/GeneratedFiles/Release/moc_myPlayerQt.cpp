/****************************************************************************
** Meta object code from reading C++ file 'myPlayerQt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myPlayerQt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myPlayerQt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myPlayerQt_t {
    QByteArrayData data[22];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myPlayerQt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myPlayerQt_t qt_meta_stringdata_myPlayerQt = {
    {
QT_MOC_LITERAL(0, 0, 10), // "myPlayerQt"
QT_MOC_LITERAL(1, 11, 7), // "sendPos"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 3), // "pos"
QT_MOC_LITERAL(4, 24, 4), // "open"
QT_MOC_LITERAL(5, 29, 15), // "netAddressInput"
QT_MOC_LITERAL(6, 45, 4), // "play"
QT_MOC_LITERAL(7, 50, 13), // "sliderPressed"
QT_MOC_LITERAL(8, 64, 13), // "sliderRelease"
QT_MOC_LITERAL(9, 78, 7), // "setMute"
QT_MOC_LITERAL(10, 86, 9), // "setVolume"
QT_MOC_LITERAL(11, 96, 10), // "fullScreen"
QT_MOC_LITERAL(12, 107, 13), // "showVideoList"
QT_MOC_LITERAL(13, 121, 16), // "clickedVideoList"
QT_MOC_LITERAL(14, 138, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 155, 4), // "item"
QT_MOC_LITERAL(16, 160, 12), // "skipPrevious"
QT_MOC_LITERAL(17, 173, 8), // "skipNext"
QT_MOC_LITERAL(18, 182, 8), // "seekBack"
QT_MOC_LITERAL(19, 191, 11), // "seekForward"
QT_MOC_LITERAL(20, 203, 13), // "showPlayGroup"
QT_MOC_LITERAL(21, 217, 6) // "isShow"

    },
    "myPlayerQt\0sendPos\0\0pos\0open\0"
    "netAddressInput\0play\0sliderPressed\0"
    "sliderRelease\0setMute\0setVolume\0"
    "fullScreen\0showVideoList\0clickedVideoList\0"
    "QListWidgetItem*\0item\0skipPrevious\0"
    "skipNext\0seekBack\0seekForward\0"
    "showPlayGroup\0isShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myPlayerQt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   97,    2, 0x0a /* Public */,
       5,    0,   98,    2, 0x0a /* Public */,
       6,    0,   99,    2, 0x0a /* Public */,
       7,    0,  100,    2, 0x0a /* Public */,
       8,    0,  101,    2, 0x0a /* Public */,
       9,    0,  102,    2, 0x0a /* Public */,
      10,    0,  103,    2, 0x0a /* Public */,
      11,    0,  104,    2, 0x0a /* Public */,
      12,    0,  105,    2, 0x0a /* Public */,
      13,    1,  106,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x0a /* Public */,
      17,    0,  110,    2, 0x0a /* Public */,
      18,    0,  111,    2, 0x0a /* Public */,
      19,    0,  112,    2, 0x0a /* Public */,
      20,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,

       0        // eod
};

void myPlayerQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myPlayerQt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPos((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->open(); break;
        case 2: _t->netAddressInput(); break;
        case 3: _t->play(); break;
        case 4: _t->sliderPressed(); break;
        case 5: _t->sliderRelease(); break;
        case 6: _t->setMute(); break;
        case 7: _t->setVolume(); break;
        case 8: _t->fullScreen(); break;
        case 9: _t->showVideoList(); break;
        case 10: _t->clickedVideoList((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->skipPrevious(); break;
        case 12: _t->skipNext(); break;
        case 13: _t->seekBack(); break;
        case 14: _t->seekForward(); break;
        case 15: _t->showPlayGroup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myPlayerQt::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myPlayerQt::sendPos)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myPlayerQt::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_myPlayerQt.data,
    qt_meta_data_myPlayerQt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myPlayerQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myPlayerQt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myPlayerQt.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int myPlayerQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void myPlayerQt::sendPos(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
