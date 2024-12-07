/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_pushButton_Ajouter_clicked",
    "",
    "on_comboBox_etat_activated",
    "index",
    "on_comboBox_type_activated",
    "on_pushButton_Supprimer_clicked",
    "on_pushButton_Annuler_clicked",
    "on_lineEdit_ID_editingFinished",
    "on_pushButton_tri_clicked",
    "on_pushButton_Recherche_clicked",
    "on_tableView_clicked",
    "QModelIndex",
    "on_qrcode_button_clicked",
    "on_tabWidget_currentChanged",
    "on_pushButton_SMS_clicked",
    "on_pushButton_exporter_2_clicked",
    "rafraichirTable",
    "on_comboBox_statut_activated",
    "on_comboBox_type_2_activated",
    "on_comboBox_mode_activated",
    "on_annuler_clicked",
    "on_supprimer_clicked",
    "on_trier_clicked",
    "on_rechercher_clicked",
    "on_exporter_clicked",
    "on_pushButton_statistiques_clicked",
    "on_modifier_clicked",
    "on_ajouter_clicked",
    "on_enregistrer_clicked",
    "on_comboBoxCritere_activated",
    "on_comboBox_criteria_activated"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[11];
    char stringdata1[30];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[6];
    char stringdata5[27];
    char stringdata6[32];
    char stringdata7[30];
    char stringdata8[31];
    char stringdata9[26];
    char stringdata10[32];
    char stringdata11[21];
    char stringdata12[12];
    char stringdata13[25];
    char stringdata14[28];
    char stringdata15[26];
    char stringdata16[33];
    char stringdata17[16];
    char stringdata18[29];
    char stringdata19[29];
    char stringdata20[27];
    char stringdata21[19];
    char stringdata22[21];
    char stringdata23[17];
    char stringdata24[22];
    char stringdata25[20];
    char stringdata26[35];
    char stringdata27[20];
    char stringdata28[19];
    char stringdata29[23];
    char stringdata30[29];
    char stringdata31[31];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 29),  // "on_pushButton_Ajouter_clicked"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 26),  // "on_comboBox_etat_activated"
        QT_MOC_LITERAL(69, 5),  // "index"
        QT_MOC_LITERAL(75, 26),  // "on_comboBox_type_activated"
        QT_MOC_LITERAL(102, 31),  // "on_pushButton_Supprimer_clicked"
        QT_MOC_LITERAL(134, 29),  // "on_pushButton_Annuler_clicked"
        QT_MOC_LITERAL(164, 30),  // "on_lineEdit_ID_editingFinished"
        QT_MOC_LITERAL(195, 25),  // "on_pushButton_tri_clicked"
        QT_MOC_LITERAL(221, 31),  // "on_pushButton_Recherche_clicked"
        QT_MOC_LITERAL(253, 20),  // "on_tableView_clicked"
        QT_MOC_LITERAL(274, 11),  // "QModelIndex"
        QT_MOC_LITERAL(286, 24),  // "on_qrcode_button_clicked"
        QT_MOC_LITERAL(311, 27),  // "on_tabWidget_currentChanged"
        QT_MOC_LITERAL(339, 25),  // "on_pushButton_SMS_clicked"
        QT_MOC_LITERAL(365, 32),  // "on_pushButton_exporter_2_clicked"
        QT_MOC_LITERAL(398, 15),  // "rafraichirTable"
        QT_MOC_LITERAL(414, 28),  // "on_comboBox_statut_activated"
        QT_MOC_LITERAL(443, 28),  // "on_comboBox_type_2_activated"
        QT_MOC_LITERAL(472, 26),  // "on_comboBox_mode_activated"
        QT_MOC_LITERAL(499, 18),  // "on_annuler_clicked"
        QT_MOC_LITERAL(518, 20),  // "on_supprimer_clicked"
        QT_MOC_LITERAL(539, 16),  // "on_trier_clicked"
        QT_MOC_LITERAL(556, 21),  // "on_rechercher_clicked"
        QT_MOC_LITERAL(578, 19),  // "on_exporter_clicked"
        QT_MOC_LITERAL(598, 34),  // "on_pushButton_statistiques_cl..."
        QT_MOC_LITERAL(633, 19),  // "on_modifier_clicked"
        QT_MOC_LITERAL(653, 18),  // "on_ajouter_clicked"
        QT_MOC_LITERAL(672, 22),  // "on_enregistrer_clicked"
        QT_MOC_LITERAL(695, 28),  // "on_comboBoxCritere_activated"
        QT_MOC_LITERAL(724, 30)   // "on_comboBox_criteria_activated"
    },
    "MainWindow",
    "on_pushButton_Ajouter_clicked",
    "",
    "on_comboBox_etat_activated",
    "index",
    "on_comboBox_type_activated",
    "on_pushButton_Supprimer_clicked",
    "on_pushButton_Annuler_clicked",
    "on_lineEdit_ID_editingFinished",
    "on_pushButton_tri_clicked",
    "on_pushButton_Recherche_clicked",
    "on_tableView_clicked",
    "QModelIndex",
    "on_qrcode_button_clicked",
    "on_tabWidget_currentChanged",
    "on_pushButton_SMS_clicked",
    "on_pushButton_exporter_2_clicked",
    "rafraichirTable",
    "on_comboBox_statut_activated",
    "on_comboBox_type_2_activated",
    "on_comboBox_mode_activated",
    "on_annuler_clicked",
    "on_supprimer_clicked",
    "on_trier_clicked",
    "on_rechercher_clicked",
    "on_exporter_clicked",
    "on_pushButton_statistiques_clicked",
    "on_modifier_clicked",
    "on_ajouter_clicked",
    "on_enregistrer_clicked",
    "on_comboBoxCritere_activated",
    "on_comboBox_criteria_activated"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  182,    2, 0x08,    1 /* Private */,
       3,    1,  183,    2, 0x08,    2 /* Private */,
       5,    1,  186,    2, 0x08,    4 /* Private */,
       6,    0,  189,    2, 0x08,    6 /* Private */,
       7,    0,  190,    2, 0x08,    7 /* Private */,
       8,    0,  191,    2, 0x08,    8 /* Private */,
       9,    0,  192,    2, 0x08,    9 /* Private */,
      10,    0,  193,    2, 0x08,   10 /* Private */,
      11,    1,  194,    2, 0x08,   11 /* Private */,
      13,    0,  197,    2, 0x08,   13 /* Private */,
      14,    0,  198,    2, 0x08,   14 /* Private */,
      15,    0,  199,    2, 0x08,   15 /* Private */,
      16,    0,  200,    2, 0x08,   16 /* Private */,
      17,    0,  201,    2, 0x08,   17 /* Private */,
      18,    1,  202,    2, 0x08,   18 /* Private */,
      19,    1,  205,    2, 0x08,   20 /* Private */,
      20,    1,  208,    2, 0x08,   22 /* Private */,
      21,    0,  211,    2, 0x08,   24 /* Private */,
      22,    0,  212,    2, 0x08,   25 /* Private */,
      23,    0,  213,    2, 0x08,   26 /* Private */,
      24,    0,  214,    2, 0x08,   27 /* Private */,
      25,    0,  215,    2, 0x08,   28 /* Private */,
      26,    0,  216,    2, 0x08,   29 /* Private */,
      27,    0,  217,    2, 0x08,   30 /* Private */,
      28,    0,  218,    2, 0x08,   31 /* Private */,
      29,    0,  219,    2, 0x08,   32 /* Private */,
      30,    1,  220,    2, 0x08,   33 /* Private */,
      31,    1,  223,    2, 0x08,   35 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_pushButton_Ajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_etat_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_type_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_Supprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Annuler_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_lineEdit_ID_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_tri_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Recherche_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_qrcode_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tabWidget_currentChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_SMS_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_exporter_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rafraichirTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_statut_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_type_2_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_mode_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_annuler_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_supprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_trier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rechercher_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exporter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_statistiques_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_modifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_enregistrer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBoxCritere_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_criteria_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_Ajouter_clicked(); break;
        case 1: _t->on_comboBox_etat_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->on_comboBox_type_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_pushButton_Supprimer_clicked(); break;
        case 4: _t->on_pushButton_Annuler_clicked(); break;
        case 5: _t->on_lineEdit_ID_editingFinished(); break;
        case 6: _t->on_pushButton_tri_clicked(); break;
        case 7: _t->on_pushButton_Recherche_clicked(); break;
        case 8: _t->on_tableView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 9: _t->on_qrcode_button_clicked(); break;
        case 10: _t->on_tabWidget_currentChanged(); break;
        case 11: _t->on_pushButton_SMS_clicked(); break;
        //case 12: _t->on_pushButton_exporter_2_clicked(); break;
        case 13: _t->rafraichirTable(); break;
        case 14: _t->on_comboBox_statut_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->on_comboBox_type_2_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->on_comboBox_mode_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->on_annuler_clicked(); break;
        case 18: _t->on_supprimer_clicked(); break;
        case 19: _t->on_trier_clicked(); break;
        case 20: _t->on_rechercher_clicked(); break;
        case 21: _t->on_exporter_clicked(); break;
        case 22: _t->on_pushButton_statistiques_clicked(); break;
        case 23: _t->on_modifier_clicked(); break;
        case 24: _t->on_ajouter_clicked(); break;
        case 25: _t->on_enregistrer_clicked(); break;
        case 26: _t->on_comboBoxCritere_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->on_comboBox_criteria_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
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
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP
