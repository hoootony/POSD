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
struct qt_meta_stringdata_GraphicalUI_t {
    QByteArrayData data[24];
    char stringdata[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicalUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicalUI_t qt_meta_stringdata_GraphicalUI = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 10),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 23),
QT_MOC_LITERAL(4, 48, 21),
QT_MOC_LITERAL(5, 70, 21),
QT_MOC_LITERAL(6, 92, 14),
QT_MOC_LITERAL(7, 107, 16),
QT_MOC_LITERAL(8, 124, 18),
QT_MOC_LITERAL(9, 143, 20),
QT_MOC_LITERAL(10, 164, 19),
QT_MOC_LITERAL(11, 184, 5),
QT_MOC_LITERAL(12, 190, 9),
QT_MOC_LITERAL(13, 200, 10),
QT_MOC_LITERAL(14, 211, 11),
QT_MOC_LITERAL(15, 223, 9),
QT_MOC_LITERAL(16, 233, 10),
QT_MOC_LITERAL(17, 244, 10),
QT_MOC_LITERAL(18, 255, 18),
QT_MOC_LITERAL(19, 274, 15),
QT_MOC_LITERAL(20, 290, 17),
QT_MOC_LITERAL(21, 308, 17),
QT_MOC_LITERAL(22, 326, 12),
QT_MOC_LITERAL(23, 339, 14)
    },
    "GraphicalUI\0actionExit\0\0actionCreateGraphicalUI\0"
    "actionLoadGraphicalUI\0actionSaveGraphicalUI\0"
    "actionEditNode\0actionDeleteNode\0"
    "actionInsertAChild\0actionInsertASibling\0"
    "actionInsertAParent\0about\0actionCut\0"
    "actionCopy\0actionPaste\0refreshUI\0"
    "actionUndo\0actionRedo\0actionAddRectangle\0"
    "actionAddCircle\0actionAddTriangle\0"
    "actionCleanStyles\0actionMoveUp\0"
    "actionMoveDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicalUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x0a /* Public */,
       3,    0,  125,    2, 0x0a /* Public */,
       4,    0,  126,    2, 0x0a /* Public */,
       5,    0,  127,    2, 0x0a /* Public */,
       6,    0,  128,    2, 0x0a /* Public */,
       7,    0,  129,    2, 0x0a /* Public */,
       8,    0,  130,    2, 0x0a /* Public */,
       9,    0,  131,    2, 0x0a /* Public */,
      10,    0,  132,    2, 0x0a /* Public */,
      11,    0,  133,    2, 0x0a /* Public */,
      12,    0,  134,    2, 0x0a /* Public */,
      13,    0,  135,    2, 0x0a /* Public */,
      14,    0,  136,    2, 0x0a /* Public */,
      15,    0,  137,    2, 0x0a /* Public */,
      16,    0,  138,    2, 0x0a /* Public */,
      17,    0,  139,    2, 0x0a /* Public */,
      18,    0,  140,    2, 0x0a /* Public */,
      19,    0,  141,    2, 0x0a /* Public */,
      20,    0,  142,    2, 0x0a /* Public */,
      21,    0,  143,    2, 0x0a /* Public */,
      22,    0,  144,    2, 0x0a /* Public */,
      23,    0,  145,    2, 0x0a /* Public */,

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

void GraphicalUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicalUI *_t = static_cast<GraphicalUI *>(_o);
        switch (_id) {
        case 0: _t->actionExit(); break;
        case 1: _t->actionCreateGraphicalUI(); break;
        case 2: _t->actionLoadGraphicalUI(); break;
        case 3: _t->actionSaveGraphicalUI(); break;
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
        case 14: _t->actionUndo(); break;
        case 15: _t->actionRedo(); break;
        case 16: _t->actionAddRectangle(); break;
        case 17: _t->actionAddCircle(); break;
        case 18: _t->actionAddTriangle(); break;
        case 19: _t->actionCleanStyles(); break;
        case 20: _t->actionMoveUp(); break;
        case 21: _t->actionMoveDown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GraphicalUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GraphicalUI.data,
      qt_meta_data_GraphicalUI,  qt_static_metacall, 0, 0}
};


const QMetaObject *GraphicalUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicalUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicalUI.stringdata))
        return static_cast<void*>(const_cast< GraphicalUI*>(this));
    if (!strcmp(_clname, "IObserver"))
        return static_cast< IObserver*>(const_cast< GraphicalUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GraphicalUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
