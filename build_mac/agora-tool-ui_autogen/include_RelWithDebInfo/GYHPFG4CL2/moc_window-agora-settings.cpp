/****************************************************************************
** Meta object code from reading C++ file 'window-agora-settings.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/forms/window-agora-settings.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window-agora-settings.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AgoraSettings_t {
    QByteArrayData data[13];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AgoraSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AgoraSettings_t qt_meta_stringdata_AgoraSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AgoraSettings"
QT_MOC_LITERAL(1, 14, 12), // "VideoChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "AudioChanged"
QT_MOC_LITERAL(4, 41, 14), // "GeneralChanged"
QT_MOC_LITERAL(5, 56, 22), // "on_buttonAppid_clicked"
QT_MOC_LITERAL(6, 79, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(7, 100, 16), // "QAbstractButton*"
QT_MOC_LITERAL(8, 117, 6), // "button"
QT_MOC_LITERAL(9, 124, 27), // "on_loadConfigButton_clicked"
QT_MOC_LITERAL(10, 152, 31), // "on_recordVolumeSld_valueChanged"
QT_MOC_LITERAL(11, 184, 5), // "value"
QT_MOC_LITERAL(12, 190, 32) // "on_playoutVolumeSld_valueChanged"

    },
    "AgoraSettings\0VideoChanged\0\0AudioChanged\0"
    "GeneralChanged\0on_buttonAppid_clicked\0"
    "on_buttonBox_clicked\0QAbstractButton*\0"
    "button\0on_loadConfigButton_clicked\0"
    "on_recordVolumeSld_valueChanged\0value\0"
    "on_playoutVolumeSld_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AgoraSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    1,   58,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    1,   62,    2, 0x08 /* Private */,
      12,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void AgoraSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AgoraSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->VideoChanged(); break;
        case 1: _t->AudioChanged(); break;
        case 2: _t->GeneralChanged(); break;
        case 3: _t->on_buttonAppid_clicked(); break;
        case 4: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 5: _t->on_loadConfigButton_clicked(); break;
        case 6: _t->on_recordVolumeSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_playoutVolumeSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AgoraSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AgoraSettings.data,
    qt_meta_data_AgoraSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AgoraSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgoraSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AgoraSettings.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AgoraSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
