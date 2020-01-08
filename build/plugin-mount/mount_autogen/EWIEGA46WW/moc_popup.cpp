/****************************************************************************
** Meta object code from reading C++ file 'popup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../plugin-mount/popup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'popup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Popup_t {
    QByteArrayData data[12];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Popup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Popup_t qt_meta_stringdata_Popup = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Popup"
QT_MOC_LITERAL(1, 6, 17), // "visibilityChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "visible"
QT_MOC_LITERAL(4, 33, 11), // "deviceAdded"
QT_MOC_LITERAL(5, 45, 13), // "Solid::Device"
QT_MOC_LITERAL(6, 59, 6), // "device"
QT_MOC_LITERAL(7, 66, 13), // "deviceRemoved"
QT_MOC_LITERAL(8, 80, 8), // "showHide"
QT_MOC_LITERAL(9, 89, 13), // "onDeviceAdded"
QT_MOC_LITERAL(10, 103, 3), // "udi"
QT_MOC_LITERAL(11, 107, 15) // "onDeviceRemoved"

    },
    "Popup\0visibilityChanged\0\0visible\0"
    "deviceAdded\0Solid::Device\0device\0"
    "deviceRemoved\0showHide\0onDeviceAdded\0"
    "udi\0onDeviceRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Popup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       7,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   53,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x08 /* Private */,
      11,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void Popup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Popup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->deviceAdded((*reinterpret_cast< Solid::Device(*)>(_a[1]))); break;
        case 2: _t->deviceRemoved((*reinterpret_cast< Solid::Device(*)>(_a[1]))); break;
        case 3: _t->showHide(); break;
        case 4: _t->onDeviceAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onDeviceRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Popup::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Popup::visibilityChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Popup::*)(Solid::Device );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Popup::deviceAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Popup::*)(Solid::Device );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Popup::deviceRemoved)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Popup::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Popup.data,
    qt_meta_data_Popup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Popup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Popup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Popup.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Popup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Popup::visibilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Popup::deviceAdded(Solid::Device _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Popup::deviceRemoved(Solid::Device _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
