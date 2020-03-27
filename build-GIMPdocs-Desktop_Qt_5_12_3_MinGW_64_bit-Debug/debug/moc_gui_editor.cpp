/****************************************************************************
** Meta object code from reading C++ file 'gui_editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLIENT/GUI/editorWindow/gui_editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_Editor_t {
    QByteArrayData data[17];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_Editor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_Editor_t qt_meta_stringdata_GUI_Editor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GUI_Editor"
QT_MOC_LITERAL(1, 11, 15), // "menuTools_event"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "menuTools"
QT_MOC_LITERAL(4, 38, 4), // "code"
QT_MOC_LITERAL(5, 43, 12), // "launchSetUi1"
QT_MOC_LITERAL(6, 56, 25), // "on_actionApplyUsersColors"
QT_MOC_LITERAL(7, 82, 24), // "on_actionApplyTextColors"
QT_MOC_LITERAL(8, 107, 13), // "on_actionBold"
QT_MOC_LITERAL(9, 121, 15), // "on_actionItalic"
QT_MOC_LITERAL(10, 137, 19), // "on_actionUnderlined"
QT_MOC_LITERAL(11, 157, 22), // "on_actionStrikethrough"
QT_MOC_LITERAL(12, 180, 13), // "on_actionLeft"
QT_MOC_LITERAL(13, 194, 15), // "on_actionCenter"
QT_MOC_LITERAL(14, 210, 14), // "on_actionRight"
QT_MOC_LITERAL(15, 225, 18), // "on_actionJustified"
QT_MOC_LITERAL(16, 244, 17) // "setMenuToolStatus"

    },
    "GUI_Editor\0menuTools_event\0\0menuTools\0"
    "code\0launchSetUi1\0on_actionApplyUsersColors\0"
    "on_actionApplyTextColors\0on_actionBold\0"
    "on_actionItalic\0on_actionUnderlined\0"
    "on_actionStrikethrough\0on_actionLeft\0"
    "on_actionCenter\0on_actionRight\0"
    "on_actionJustified\0setMenuToolStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI_Editor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

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
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GUI_Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI_Editor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->menuTools_event((*reinterpret_cast< menuTools(*)>(_a[1]))); break;
        case 1: _t->launchSetUi1(); break;
        case 2: _t->on_actionApplyUsersColors(); break;
        case 3: _t->on_actionApplyTextColors(); break;
        case 4: _t->on_actionBold(); break;
        case 5: _t->on_actionItalic(); break;
        case 6: _t->on_actionUnderlined(); break;
        case 7: _t->on_actionStrikethrough(); break;
        case 8: _t->on_actionLeft(); break;
        case 9: _t->on_actionCenter(); break;
        case 10: _t->on_actionRight(); break;
        case 11: _t->on_actionJustified(); break;
        case 12: _t->setMenuToolStatus((*reinterpret_cast< menuTools(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GUI_Editor::*)(menuTools );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI_Editor::menuTools_event)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUI_Editor::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GUI_Editor.data,
    qt_meta_data_GUI_Editor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUI_Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI_Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Editor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI_Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GUI_Editor::menuTools_event(menuTools _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
