/****************************************************************************
** Meta object code from reading C++ file 'configpaneldialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../panel/config/configpaneldialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configpaneldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigPanelDialog_t {
    QByteArrayData data[10];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigPanelDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigPanelDialog_t qt_meta_stringdata_ConfigPanelDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ConfigPanelDialog"
QT_MOC_LITERAL(1, 18, 7), // "testsig"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "configPosition_top"
QT_MOC_LITERAL(4, 46, 21), // "configPosition_bottom"
QT_MOC_LITERAL(5, 68, 19), // "configPosition_left"
QT_MOC_LITERAL(6, 88, 20), // "configPosition_right"
QT_MOC_LITERAL(7, 109, 17), // "configPanelSize_m"
QT_MOC_LITERAL(8, 127, 17), // "configPanelSize_l"
QT_MOC_LITERAL(9, 145, 17) // "configPanelSize_S"

    },
    "ConfigPanelDialog\0testsig\0\0"
    "configPosition_top\0configPosition_bottom\0"
    "configPosition_left\0configPosition_right\0"
    "configPanelSize_m\0configPanelSize_l\0"
    "configPanelSize_S"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigPanelDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConfigPanelDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigPanelDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testsig(); break;
        case 1: _t->configPosition_top(); break;
        case 2: _t->configPosition_bottom(); break;
        case 3: _t->configPosition_left(); break;
        case 4: _t->configPosition_right(); break;
        case 5: _t->configPanelSize_m(); break;
        case 6: _t->configPanelSize_l(); break;
        case 7: _t->configPanelSize_S(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigPanelDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigPanelDialog::testsig)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ConfigPanelDialog::staticMetaObject = { {
    &LXQt::ConfigDialog::staticMetaObject,
    qt_meta_stringdata_ConfigPanelDialog.data,
    qt_meta_data_ConfigPanelDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigPanelDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigPanelDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigPanelDialog.stringdata0))
        return static_cast<void*>(this);
    return LXQt::ConfigDialog::qt_metacast(_clname);
}

int ConfigPanelDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = LXQt::ConfigDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ConfigPanelDialog::testsig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
