/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11CameraSceneE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11CameraSceneE = QtMocHelpers::stringData(
    "CameraScene"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11CameraSceneE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject CameraScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_ZN11CameraSceneE.offsetsAndSizes,
    qt_meta_data_ZN11CameraSceneE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11CameraSceneE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CameraScene, std::true_type>
    >,
    nullptr
} };

void CameraScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CameraScene *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *CameraScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11CameraSceneE.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int CameraScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "node1Connected",
    "",
    "node1Disconnected",
    "node1DataReceived",
    "node2Connected",
    "node2Disconnected",
    "node2DataReceived",
    "tryReconnect",
    "onNewVideoFrame",
    "QVideoFrame",
    "frame",
    "onEngageClicked",
    "onFireClicked",
    "onZoomIn",
    "onZoomOut",
    "onZoomReset",
    "onBrightnessUp",
    "onBrightnessDown",
    "onFovUp",
    "onFovDown",
    "on_PB_LRF_clicked",
    "on_PB_Polarity_clicked",
    "on_PB_NUC_clicked",
    "on_PB_Home_clicked",
    "on_PB_Zoom_clicked",
    "on_PB_Fire_clicked",
    "on_PB_Plus_clicked",
    "on_PB_Minus_clicked",
    "on_PB_RequestRelease_clicked",
    "on_PB_EngageLauncher_clicked",
    "on_PB_MissileSelection_clicked",
    "on_PB_MissileEngage_clicked",
    "on_PB_Focus_clicked",
    "on_PB_ExposureGain_clicked",
    "on_PB_DayCamera_clicked",
    "on_PB_login_clicked",
    "on_PB_Cancel_clicked",
    "on_PB_View_clicked",
    "on_PB_LogOut_clicked",
    "on_PB_pageMaintenance_clicked",
    "on_PB_pageStatusPanel_clicked",
    "on_PB_PreviousPage_clicked",
    "on_PB_Logout_clicked",
    "on_PB_PreviousPage_2_clicked",
    "on_PB_Logout_2_clicked",
    "myfunction",
    "onRecordButtonClicked",
    "onRecordingStarted",
    "onRecordingStopped",
    "filePath",
    "onRecordingError",
    "errorMessage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  296,    2, 0x08,    1 /* Private */,
       3,    0,  297,    2, 0x08,    2 /* Private */,
       4,    0,  298,    2, 0x08,    3 /* Private */,
       5,    0,  299,    2, 0x08,    4 /* Private */,
       6,    0,  300,    2, 0x08,    5 /* Private */,
       7,    0,  301,    2, 0x08,    6 /* Private */,
       8,    0,  302,    2, 0x08,    7 /* Private */,
       9,    1,  303,    2, 0x08,    8 /* Private */,
      12,    0,  306,    2, 0x08,   10 /* Private */,
      13,    0,  307,    2, 0x08,   11 /* Private */,
      14,    0,  308,    2, 0x08,   12 /* Private */,
      15,    0,  309,    2, 0x08,   13 /* Private */,
      16,    0,  310,    2, 0x08,   14 /* Private */,
      17,    0,  311,    2, 0x08,   15 /* Private */,
      18,    0,  312,    2, 0x08,   16 /* Private */,
      19,    0,  313,    2, 0x08,   17 /* Private */,
      20,    0,  314,    2, 0x08,   18 /* Private */,
      21,    0,  315,    2, 0x08,   19 /* Private */,
      22,    0,  316,    2, 0x08,   20 /* Private */,
      23,    0,  317,    2, 0x08,   21 /* Private */,
      24,    0,  318,    2, 0x08,   22 /* Private */,
      25,    0,  319,    2, 0x08,   23 /* Private */,
      26,    0,  320,    2, 0x08,   24 /* Private */,
      27,    0,  321,    2, 0x08,   25 /* Private */,
      28,    0,  322,    2, 0x08,   26 /* Private */,
      29,    0,  323,    2, 0x08,   27 /* Private */,
      30,    0,  324,    2, 0x08,   28 /* Private */,
      31,    0,  325,    2, 0x08,   29 /* Private */,
      32,    0,  326,    2, 0x08,   30 /* Private */,
      33,    0,  327,    2, 0x08,   31 /* Private */,
      34,    0,  328,    2, 0x08,   32 /* Private */,
      35,    0,  329,    2, 0x08,   33 /* Private */,
      36,    0,  330,    2, 0x08,   34 /* Private */,
      37,    0,  331,    2, 0x08,   35 /* Private */,
      38,    0,  332,    2, 0x08,   36 /* Private */,
      39,    0,  333,    2, 0x08,   37 /* Private */,
      40,    0,  334,    2, 0x08,   38 /* Private */,
      41,    0,  335,    2, 0x08,   39 /* Private */,
      42,    0,  336,    2, 0x08,   40 /* Private */,
      43,    0,  337,    2, 0x08,   41 /* Private */,
      44,    0,  338,    2, 0x08,   42 /* Private */,
      45,    0,  339,    2, 0x08,   43 /* Private */,
      46,    0,  340,    2, 0x08,   44 /* Private */,
      47,    0,  341,    2, 0x08,   45 /* Private */,
      48,    0,  342,    2, 0x08,   46 /* Private */,
      49,    1,  343,    2, 0x08,   47 /* Private */,
      51,    1,  346,    2, 0x08,   49 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
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
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, QMetaType::QString,   52,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'node1Connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'node1Disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'node1DataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'node2Connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'node2Disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'node2DataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tryReconnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNewVideoFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVideoFrame &, std::false_type>,
        // method 'onEngageClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFireClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onZoomIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onZoomOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onZoomReset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBrightnessUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBrightnessDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFovUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFovDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_LRF_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Polarity_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_NUC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Home_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Zoom_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Fire_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Plus_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Minus_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_RequestRelease_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_EngageLauncher_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_MissileSelection_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_MissileEngage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Focus_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_ExposureGain_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_DayCamera_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_login_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Cancel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_View_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_LogOut_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_pageMaintenance_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_pageStatusPanel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_PreviousPage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Logout_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_PreviousPage_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_PB_Logout_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'myfunction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRecordButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRecordingStarted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRecordingStopped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRecordingError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->node1Connected(); break;
        case 1: _t->node1Disconnected(); break;
        case 2: _t->node1DataReceived(); break;
        case 3: _t->node2Connected(); break;
        case 4: _t->node2Disconnected(); break;
        case 5: _t->node2DataReceived(); break;
        case 6: _t->tryReconnect(); break;
        case 7: _t->onNewVideoFrame((*reinterpret_cast< std::add_pointer_t<QVideoFrame>>(_a[1]))); break;
        case 8: _t->onEngageClicked(); break;
        case 9: _t->onFireClicked(); break;
        case 10: _t->onZoomIn(); break;
        case 11: _t->onZoomOut(); break;
        case 12: _t->onZoomReset(); break;
        case 13: _t->onBrightnessUp(); break;
        case 14: _t->onBrightnessDown(); break;
        case 15: _t->onFovUp(); break;
        case 16: _t->onFovDown(); break;
        case 17: _t->on_PB_LRF_clicked(); break;
        case 18: _t->on_PB_Polarity_clicked(); break;
        case 19: _t->on_PB_NUC_clicked(); break;
        case 20: _t->on_PB_Home_clicked(); break;
        case 21: _t->on_PB_Zoom_clicked(); break;
        case 22: _t->on_PB_Fire_clicked(); break;
        case 23: _t->on_PB_Plus_clicked(); break;
        case 24: _t->on_PB_Minus_clicked(); break;
        case 25: _t->on_PB_RequestRelease_clicked(); break;
        case 26: _t->on_PB_EngageLauncher_clicked(); break;
        case 27: _t->on_PB_MissileSelection_clicked(); break;
        case 28: _t->on_PB_MissileEngage_clicked(); break;
        case 29: _t->on_PB_Focus_clicked(); break;
        case 30: _t->on_PB_ExposureGain_clicked(); break;
        case 31: _t->on_PB_DayCamera_clicked(); break;
        case 32: _t->on_PB_login_clicked(); break;
        case 33: _t->on_PB_Cancel_clicked(); break;
        case 34: _t->on_PB_View_clicked(); break;
        case 35: _t->on_PB_LogOut_clicked(); break;
        case 36: _t->on_PB_pageMaintenance_clicked(); break;
        case 37: _t->on_PB_pageStatusPanel_clicked(); break;
        case 38: _t->on_PB_PreviousPage_clicked(); break;
        case 39: _t->on_PB_Logout_clicked(); break;
        case 40: _t->on_PB_PreviousPage_2_clicked(); break;
        case 41: _t->on_PB_Logout_2_clicked(); break;
        case 42: _t->myfunction(); break;
        case 43: _t->onRecordButtonClicked(); break;
        case 44: _t->onRecordingStarted(); break;
        case 45: _t->onRecordingStopped((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 46: _t->onRecordingError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVideoFrame >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    }
    return _id;
}
QT_WARNING_POP
