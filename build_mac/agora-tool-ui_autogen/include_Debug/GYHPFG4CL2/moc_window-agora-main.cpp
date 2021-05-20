/****************************************************************************
** Meta object code from reading C++ file 'window-agora-main.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/forms/window-agora-main.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window-agora-main.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DisplayResizeEvent_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayResizeEvent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayResizeEvent_t qt_meta_stringdata_DisplayResizeEvent = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DisplayResizeEvent"
QT_MOC_LITERAL(1, 19, 14), // "DisplayResized"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "DisplayResizeEvent\0DisplayResized\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayResizeEvent[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void DisplayResizeEvent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DisplayResizeEvent *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayResized(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DisplayResizeEvent::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DisplayResizeEvent::DisplayResized)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DisplayResizeEvent::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DisplayResizeEvent.data,
    qt_meta_data_DisplayResizeEvent,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DisplayResizeEvent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayResizeEvent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayResizeEvent.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DisplayResizeEvent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DisplayResizeEvent::DisplayResized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_AgoraBasic_t {
    QByteArrayData data[39];
    char stringdata0[559];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AgoraBasic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AgoraBasic_t qt_meta_stringdata_AgoraBasic = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AgoraBasic"
QT_MOC_LITERAL(1, 11, 14), // "DisplayCreated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "AgoraBasic*"
QT_MOC_LITERAL(4, 39, 5), // "agora"
QT_MOC_LITERAL(5, 45, 18), // "requestTokenSignal"
QT_MOC_LITERAL(6, 64, 3), // "err"
QT_MOC_LITERAL(7, 68, 28), // "on_agoraSteramButton_clicked"
QT_MOC_LITERAL(8, 97, 25), // "on_settingsButton_clicked"
QT_MOC_LITERAL(9, 123, 21), // "on_exitButton_clicked"
QT_MOC_LITERAL(10, 145, 25), // "onJoinChannelSuccess_slot"
QT_MOC_LITERAL(11, 171, 11), // "const char*"
QT_MOC_LITERAL(12, 183, 7), // "channel"
QT_MOC_LITERAL(13, 191, 3), // "uid"
QT_MOC_LITERAL(14, 195, 7), // "elapsed"
QT_MOC_LITERAL(15, 203, 19), // "onLeaveChannel_slot"
QT_MOC_LITERAL(16, 223, 8), // "RtcStats"
QT_MOC_LITERAL(17, 232, 5), // "stats"
QT_MOC_LITERAL(18, 238, 12), // "onError_slot"
QT_MOC_LITERAL(19, 251, 3), // "msg"
QT_MOC_LITERAL(20, 255, 17), // "onUserJoined_slot"
QT_MOC_LITERAL(21, 273, 5), // "uid_t"
QT_MOC_LITERAL(22, 279, 18), // "onUserOffline_slot"
QT_MOC_LITERAL(23, 298, 6), // "reason"
QT_MOC_LITERAL(24, 305, 30), // "onFirstRemoteVideoDecoded_slot"
QT_MOC_LITERAL(25, 336, 5), // "width"
QT_MOC_LITERAL(26, 342, 6), // "height"
QT_MOC_LITERAL(27, 349, 29), // "onConnectionStateChanged_slot"
QT_MOC_LITERAL(28, 379, 5), // "state"
QT_MOC_LITERAL(29, 385, 30), // "onRemoteVideoStateChanged_slot"
QT_MOC_LITERAL(30, 416, 28), // "onFirstRemoteVideoFrame_slot"
QT_MOC_LITERAL(31, 445, 16), // "transcoding_slot"
QT_MOC_LITERAL(32, 462, 15), // "showRemote_slot"
QT_MOC_LITERAL(33, 478, 24), // "onClientRoleChanged_slot"
QT_MOC_LITERAL(34, 503, 7), // "oldRole"
QT_MOC_LITERAL(35, 511, 7), // "newRole"
QT_MOC_LITERAL(36, 519, 15), // "joinFailed_slot"
QT_MOC_LITERAL(37, 535, 18), // "reuquestToken_slot"
QT_MOC_LITERAL(38, 554, 4) // "json"

    },
    "AgoraBasic\0DisplayCreated\0\0AgoraBasic*\0"
    "agora\0requestTokenSignal\0err\0"
    "on_agoraSteramButton_clicked\0"
    "on_settingsButton_clicked\0"
    "on_exitButton_clicked\0onJoinChannelSuccess_slot\0"
    "const char*\0channel\0uid\0elapsed\0"
    "onLeaveChannel_slot\0RtcStats\0stats\0"
    "onError_slot\0msg\0onUserJoined_slot\0"
    "uid_t\0onUserOffline_slot\0reason\0"
    "onFirstRemoteVideoDecoded_slot\0width\0"
    "height\0onConnectionStateChanged_slot\0"
    "state\0onRemoteVideoStateChanged_slot\0"
    "onFirstRemoteVideoFrame_slot\0"
    "transcoding_slot\0showRemote_slot\0"
    "onClientRoleChanged_slot\0oldRole\0"
    "newRole\0joinFailed_slot\0reuquestToken_slot\0"
    "json"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AgoraBasic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       5,    2,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  117,    2, 0x0a /* Public */,
       8,    0,  118,    2, 0x0a /* Public */,
       9,    0,  119,    2, 0x0a /* Public */,
      10,    3,  120,    2, 0x0a /* Public */,
      15,    1,  127,    2, 0x0a /* Public */,
      18,    2,  130,    2, 0x0a /* Public */,
      20,    2,  135,    2, 0x0a /* Public */,
      22,    2,  140,    2, 0x0a /* Public */,
      24,    4,  145,    2, 0x0a /* Public */,
      27,    2,  154,    2, 0x0a /* Public */,
      29,    4,  159,    2, 0x0a /* Public */,
      30,    4,  168,    2, 0x0a /* Public */,
      31,    0,  177,    2, 0x0a /* Public */,
      32,    0,  178,    2, 0x0a /* Public */,
      33,    2,  179,    2, 0x0a /* Public */,
      36,    0,  184,    2, 0x0a /* Public */,
      37,    2,  185,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, QMetaType::UInt, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,    6,   19,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int,   13,   23,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   25,   26,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   23,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   28,   23,   14,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   25,   26,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   34,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   38,    6,

       0        // eod
};

void AgoraBasic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AgoraBasic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayCreated((*reinterpret_cast< AgoraBasic*(*)>(_a[1]))); break;
        case 1: _t->requestTokenSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_agoraSteramButton_clicked(); break;
        case 3: _t->on_settingsButton_clicked(); break;
        case 4: _t->on_exitButton_clicked(); break;
        case 5: _t->onJoinChannelSuccess_slot((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->onLeaveChannel_slot((*reinterpret_cast< const RtcStats(*)>(_a[1]))); break;
        case 7: _t->onError_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 8: _t->onUserJoined_slot((*reinterpret_cast< uid_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->onUserOffline_slot((*reinterpret_cast< uid_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->onFirstRemoteVideoDecoded_slot((*reinterpret_cast< uid_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 11: _t->onConnectionStateChanged_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->onRemoteVideoStateChanged_slot((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 13: _t->onFirstRemoteVideoFrame_slot((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 14: _t->transcoding_slot(); break;
        case 15: _t->showRemote_slot(); break;
        case 16: _t->onClientRoleChanged_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->joinFailed_slot(); break;
        case 18: _t->reuquestToken_slot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AgoraBasic* >(); break;
            }
            break;
        case 6:
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
            using _t = void (AgoraBasic::*)(AgoraBasic * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraBasic::DisplayCreated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AgoraBasic::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AgoraBasic::requestTokenSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AgoraBasic::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AgoraBasic.data,
    qt_meta_data_AgoraBasic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AgoraBasic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgoraBasic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AgoraBasic.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AgoraBasic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void AgoraBasic::DisplayCreated(AgoraBasic * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AgoraBasic::requestTokenSignal(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
