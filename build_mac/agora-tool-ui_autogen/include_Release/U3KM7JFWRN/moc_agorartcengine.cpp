/****************************************************************************
** Meta object code from reading C++ file 'agorartcengine.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/Agora/agorartcengine.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agorartcengine.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AgoraRtcEngine_t {
    QByteArrayData data[29];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AgoraRtcEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AgoraRtcEngine_t qt_meta_stringdata_AgoraRtcEngine = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AgoraRtcEngine"
QT_MOC_LITERAL(1, 15, 20), // "onJoinChannelSuccess"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "const char*"
QT_MOC_LITERAL(4, 49, 7), // "channel"
QT_MOC_LITERAL(5, 57, 3), // "uid"
QT_MOC_LITERAL(6, 61, 7), // "elapsed"
QT_MOC_LITERAL(7, 69, 14), // "onLeaveChannel"
QT_MOC_LITERAL(8, 84, 8), // "RtcStats"
QT_MOC_LITERAL(9, 93, 5), // "stats"
QT_MOC_LITERAL(10, 99, 7), // "onError"
QT_MOC_LITERAL(11, 107, 3), // "err"
QT_MOC_LITERAL(12, 111, 3), // "msg"
QT_MOC_LITERAL(13, 115, 12), // "onUserJoined"
QT_MOC_LITERAL(14, 128, 13), // "onUserOffline"
QT_MOC_LITERAL(15, 142, 6), // "reason"
QT_MOC_LITERAL(16, 149, 25), // "onFirstRemoteVideoDecoded"
QT_MOC_LITERAL(17, 175, 5), // "width"
QT_MOC_LITERAL(18, 181, 6), // "height"
QT_MOC_LITERAL(19, 188, 24), // "onConnectionStateChanged"
QT_MOC_LITERAL(20, 213, 5), // "state"
QT_MOC_LITERAL(21, 219, 25), // "onRemoteVideoStateChanged"
QT_MOC_LITERAL(22, 245, 23), // "onFirstRemoteVideoFrame"
QT_MOC_LITERAL(23, 269, 27), // "onRtmpStreamingStateChanged"
QT_MOC_LITERAL(24, 297, 3), // "url"
QT_MOC_LITERAL(25, 301, 7), // "errCode"
QT_MOC_LITERAL(26, 309, 19), // "onClientRoleChanged"
QT_MOC_LITERAL(27, 329, 7), // "oldRole"
QT_MOC_LITERAL(28, 337, 7) // "newRole"

    },
    "AgoraRtcEngine\0onJoinChannelSuccess\0"
    "\0const char*\0channel\0uid\0elapsed\0"
    "onLeaveChannel\0RtcStats\0stats\0onError\0"
    "err\0msg\0onUserJoined\0onUserOffline\0"
    "reason\0onFirstRemoteVideoDecoded\0width\0"
    "height\0onConnectionStateChanged\0state\0"
    "onRemoteVideoStateChanged\0"
    "onFirstRemoteVideoFrame\0"
    "onRtmpStreamingStateChanged\0url\0errCode\0"
    "onClientRoleChanged\0oldRole\0newRole"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AgoraRtcEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,
      10,    2,   79,    2, 0x06 /* Public */,
      13,    2,   84,    2, 0x06 /* Public */,
      14,    2,   89,    2, 0x06 /* Public */,
      16,    4,   94,    2, 0x06 /* Public */,
      19,    2,  103,    2, 0x06 /* Public */,
      21,    4,  108,    2, 0x06 /* Public */,
      22,    4,  117,    2, 0x06 /* Public */,
      23,    3,  126,    2, 0x06 /* Public */,
      26,    2,  133,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,   11,   12,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,    5,   15,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,   17,   18,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   15,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,   20,   15,    6,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,   17,   18,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,   24,   20,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   27,   28,

       0        // eod
};

void AgoraRtcEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AgoraRtcEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onJoinChannelSuccess((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->onLeaveChannel((*reinterpret_cast< const RtcStats(*)>(_a[1]))); break;
        case 2: _t->onError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 3: _t->onUserJoined((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onUserOffline((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onFirstRemoteVideoDecoded((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->onConnectionStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->onRemoteVideoStateChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->onFirstRemoteVideoFrame((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->onRtmpStreamingStateChanged((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->onClientRoleChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RtcStats >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AgoraRtcEngine::*)(const char * , unsigned int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onJoinChannelSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(const RtcStats & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onLeaveChannel)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(int , const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(unsigned int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onUserJoined)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(unsigned int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onUserOffline)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(unsigned int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onFirstRemoteVideoDecoded)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onConnectionStateChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(unsigned int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onRemoteVideoStateChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(unsigned  , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onFirstRemoteVideoFrame)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(const char * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onRtmpStreamingStateChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AgoraRtcEngine::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraRtcEngine::onClientRoleChanged)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AgoraRtcEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AgoraRtcEngine.data,
    qt_meta_data_AgoraRtcEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AgoraRtcEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgoraRtcEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AgoraRtcEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AgoraRtcEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AgoraRtcEngine::onJoinChannelSuccess(const char * _t1, unsigned int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AgoraRtcEngine::onLeaveChannel(const RtcStats & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AgoraRtcEngine::onError(int _t1, const char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AgoraRtcEngine::onUserJoined(unsigned int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AgoraRtcEngine::onUserOffline(unsigned int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AgoraRtcEngine::onFirstRemoteVideoDecoded(unsigned int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AgoraRtcEngine::onConnectionStateChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AgoraRtcEngine::onRemoteVideoStateChanged(unsigned int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AgoraRtcEngine::onFirstRemoteVideoFrame(unsigned  _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AgoraRtcEngine::onRtmpStreamingStateChanged(const char * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AgoraRtcEngine::onClientRoleChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
