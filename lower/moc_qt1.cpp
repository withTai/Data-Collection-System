/****************************************************************************
** Meta object code from reading C++ file 'qt1.h'
**
** Created: Thu Apr 18 00:01:21 2024
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt1.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Qt1[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      16,    4,    4,    4, 0x0a,
      26,    4,    4,    4, 0x0a,
      40,    4,    4,    4, 0x0a,
      51,    4,    4,    4, 0x0a,
      64,    4,    4,    4, 0x0a,
      75,    4,    4,    4, 0x0a,
      90,    4,    4,    4, 0x0a,
     107,    4,    4,    4, 0x0a,
     125,    4,    4,    4, 0x0a,
     137,    4,    4,    4, 0x0a,
     155,    4,    4,    4, 0x0a,
     166,    4,    4,    4, 0x0a,
     182,    4,    4,    4, 0x0a,
     201,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Qt1[] = {
    "Qt1\0\0fun_time()\0fun_pic()\0display_pic()\0"
    "fun_prev()\0fun_delete()\0fun_open()\0"
    "fun_cap_open()\0fun_take_photo()\0"
    "fun_refresh_pic()\0fun_start()\0"
    "data_collection()\0SetValue()\0"
    "fun_heartbeat()\0fun_show_history()\0"
    "fun_resistance()\0"
};

const QMetaObject Qt1::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Qt1,
      qt_meta_data_Qt1, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Qt1::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Qt1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Qt1::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qt1))
        return static_cast<void*>(const_cast< Qt1*>(this));
    if (!strcmp(_clname, "Ui_Qt1"))
        return static_cast< Ui_Qt1*>(const_cast< Qt1*>(this));
    return QDialog::qt_metacast(_clname);
}

int Qt1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fun_time(); break;
        case 1: fun_pic(); break;
        case 2: display_pic(); break;
        case 3: fun_prev(); break;
        case 4: fun_delete(); break;
        case 5: fun_open(); break;
        case 6: fun_cap_open(); break;
        case 7: fun_take_photo(); break;
        case 8: fun_refresh_pic(); break;
        case 9: fun_start(); break;
        case 10: data_collection(); break;
        case 11: SetValue(); break;
        case 12: fun_heartbeat(); break;
        case 13: fun_show_history(); break;
        case 14: fun_resistance(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
