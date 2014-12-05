/****************************************************************************
** Meta object code from reading C++ file 'GraphicalUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GraphicalUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicalUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MindMap_t {
    QByteArrayData data[16];
    char stringdata[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MindMap_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MindMap_t qt_meta_stringdata_MindMap = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 10),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 19),
QT_MOC_LITERAL(4, 40, 17),
QT_MOC_LITERAL(5, 58, 17),
QT_MOC_LITERAL(6, 76, 14),
QT_MOC_LITERAL(7, 91, 16),
QT_MOC_LITERAL(8, 108, 18),
QT_MOC_LITERAL(9, 127, 20),
QT_MOC_LITERAL(10, 148, 19),
QT_MOC_LITERAL(11, 168, 5),
QT_MOC_LITERAL(12, 174, 9),
QT_MOC_LITERAL(13, 184, 10),
QT_MOC_LITERAL(14, 195, 11),
QT_MOC_LITERAL(15, 207, 9)
    },
    "MindMap\0actionExit\0\0actionCreateMindMap\0"
    "actionLoadMindMap\0actionSaveMindMap\0"
    "actionEditNode\0actionDeleteNode\0"
    "actionInsertAChild\0actionInsertASibling\0"
    "actionInsertAParent\0about\0actionCut\0"
    "actionCopy\0actionPaste\0refreshUI"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MindMap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MindMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MindMap *_t = static_cast<MindMap *>(_o);
        switch (_id) {
        case 0: _t->actionExit(); break;
        case 1: _t->actionCreateMindMap(); break;
        case 2: _t->actionLoadMindMap(); break;
        case 3: _t->actionSaveMindMap(); break;
        case 4: _t->actionEditNode(); break;
        case 5: _t->actionDeleteNode(); break;
        case 6: _t->actionInsertAChild(); break;
        case 7: _t->actionInsertASibling(); break;
        case 8: _t->actionInsertAParent(); break;
        case 9: _t->about(); break;
        case 10: _t->actionCut(); break;
        case 11: _t->actionCopy(); break;
        case 12: _t->actionPaste(); break;
        case 13: _t->refreshUI(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MindMap::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MindMap.data,
      qt_meta_data_MindMap,  qt_static_metacall, 0, 0}
};


const QMetaObject *MindMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MindMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MindMap.stringdata))
        return static_cast<void*>(const_cast< MindMap*>(this));
    if (!strcmp(_clname, "IObserver"))
        return static_cast< IObserver*>(const_cast< MindMap*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MindMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
