/****************************************************************************
** Meta object code from reading C++ file 'captureWorker.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../IDS Deployable/Qt_IDS_Interface/captureWorker.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'captureWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN13CaptureWorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto CaptureWorker::qt_create_metaobjectdata<qt_meta_tag_ZN13CaptureWorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CaptureWorker",
        "packetReady",
        "",
        "timeStamp",
        "sourceIP",
        "destIP",
        "proto",
        "len",
        "sourcePort",
        "destPort",
        "error",
        "message",
        "finished",
        "process"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'packetReady'
        QtMocHelpers::SignalData<void(QString, QString, QString, QString, int, int, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 }, { QMetaType::QString, 5 }, { QMetaType::QString, 6 },
            { QMetaType::Int, 7 }, { QMetaType::Int, 8 }, { QMetaType::Int, 9 },
        }}),
        // Signal 'error'
        QtMocHelpers::SignalData<void(QString)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'finished'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'process'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CaptureWorker, qt_meta_tag_ZN13CaptureWorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CaptureWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CaptureWorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CaptureWorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13CaptureWorkerE_t>.metaTypes,
    nullptr
} };

void CaptureWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CaptureWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->packetReady((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7]))); break;
        case 1: _t->error((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->finished(); break;
        case 3: _t->process(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CaptureWorker::*)(QString , QString , QString , QString , int , int , int )>(_a, &CaptureWorker::packetReady, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CaptureWorker::*)(QString )>(_a, &CaptureWorker::error, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CaptureWorker::*)()>(_a, &CaptureWorker::finished, 2))
            return;
    }
}

const QMetaObject *CaptureWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaptureWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CaptureWorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CaptureWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CaptureWorker::packetReady(QString _t1, QString _t2, QString _t3, QString _t4, int _t5, int _t6, int _t7)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}

// SIGNAL 1
void CaptureWorker::error(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void CaptureWorker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
