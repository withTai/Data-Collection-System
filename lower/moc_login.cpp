/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created: Thu Apr 18 00:01:21 2024
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "login.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Login[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      29,    6,    6,    6, 0x08,
      50,    6,    6,    6, 0x08,
      68,    6,    6,    6, 0x08,
      86,    6,    6,    6, 0x08,
     104,    6,    6,    6, 0x08,
     122,    6,    6,    6, 0x08,
     140,    6,    6,    6, 0x08,
     158,    6,    6,    6, 0x08,
     176,    6,    6,    6, 0x08,
     194,    6,    6,    6, 0x08,
     212,    6,    6,    6, 0x08,
     230,    6,    6,    6, 0x08,
     252,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Login[] = {
    "Login\0\0on_pb_login_clicked()\0"
    "on_pb_quit_clicked()\0on_pb_1_clicked()\0"
    "on_pb_2_clicked()\0on_pb_3_clicked()\0"
    "on_pb_0_clicked()\0on_pb_4_clicked()\0"
    "on_pb_5_clicked()\0on_pb_6_clicked()\0"
    "on_pb_7_clicked()\0on_pb_8_clicked()\0"
    "on_pb_9_clicked()\0on_pb_clear_clicked()\0"
    "on_pb_input_clicked()\0"
};

const QMetaObject Login::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Login,
      qt_meta_data_Login, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Login::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Login::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Login))
        return static_cast<void*>(const_cast< Login*>(this));
    return QWidget::qt_metacast(_clname);
}

int Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pb_login_clicked(); break;
        case 1: on_pb_quit_clicked(); break;
        case 2: on_pb_1_clicked(); break;
        case 3: on_pb_2_clicked(); break;
        case 4: on_pb_3_clicked(); break;
        case 5: on_pb_0_clicked(); break;
        case 6: on_pb_4_clicked(); break;
        case 7: on_pb_5_clicked(); break;
        case 8: on_pb_6_clicked(); break;
        case 9: on_pb_7_clicked(); break;
        case 10: on_pb_8_clicked(); break;
        case 11: on_pb_9_clicked(); break;
        case 12: on_pb_clear_clicked(); break;
        case 13: on_pb_input_clicked(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
