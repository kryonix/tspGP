/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QLabel *label;
    QSpinBox *spinBoxLocations;
    QLabel *label_2;
    QSpinBox *spinBoxIndividuen;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxMutationrate;
    QCheckBox *checkBoxReverse;
    QCheckBox *checkBoxMultiThreading;
    QLabel *label_3;
    QSpinBox *spinBoxThreads;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QGroupBox *groupBox_2;
    QRadioButton *radioButtonZufall;
    QRadioButton *radioButtonKreis;
    QRadioButton *radioButtonRaster;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(792, 521);
        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 500, 500));
        widget->setMinimumSize(QSize(500, 500));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(520, 450, 71, 23));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(520, 10, 231, 271));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 46, 21));
        spinBoxLocations = new QSpinBox(groupBox);
        spinBoxLocations->setObjectName(QStringLiteral("spinBoxLocations"));
        spinBoxLocations->setGeometry(QRect(150, 20, 71, 22));
        spinBoxLocations->setMinimum(6);
        spinBoxLocations->setMaximum(100000);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 91, 21));
        spinBoxIndividuen = new QSpinBox(groupBox);
        spinBoxIndividuen->setObjectName(QStringLiteral("spinBoxIndividuen"));
        spinBoxIndividuen->setGeometry(QRect(150, 50, 71, 22));
        spinBoxIndividuen->setMinimum(2);
        spinBoxIndividuen->setMaximum(10000);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 71, 21));
        doubleSpinBoxMutationrate = new QDoubleSpinBox(groupBox);
        doubleSpinBoxMutationrate->setObjectName(QStringLiteral("doubleSpinBoxMutationrate"));
        doubleSpinBoxMutationrate->setGeometry(QRect(150, 80, 71, 22));
        doubleSpinBoxMutationrate->setDecimals(1);
        doubleSpinBoxMutationrate->setMinimum(-1);
        doubleSpinBoxMutationrate->setValue(10);
        checkBoxReverse = new QCheckBox(groupBox);
        checkBoxReverse->setObjectName(QStringLiteral("checkBoxReverse"));
        checkBoxReverse->setGeometry(QRect(10, 240, 70, 17));
        checkBoxMultiThreading = new QCheckBox(groupBox);
        checkBoxMultiThreading->setObjectName(QStringLiteral("checkBoxMultiThreading"));
        checkBoxMultiThreading->setEnabled(true);
        checkBoxMultiThreading->setGeometry(QRect(10, 220, 91, 17));
        checkBoxMultiThreading->setChecked(false);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 46, 13));
        spinBoxThreads = new QSpinBox(groupBox);
        spinBoxThreads->setObjectName(QStringLiteral("spinBoxThreads"));
        spinBoxThreads->setGeometry(QRect(150, 110, 71, 22));
        spinBoxThreads->setMinimum(1);
        spinBoxThreads->setMaximum(100);
        spinBoxThreads->setValue(100);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(true);
        pushButton_2->setGeometry(QRect(110, 80, 31, 23));
        pushButton_2->setCheckable(false);
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(110, 50, 31, 23));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(600, 450, 71, 23));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(520, 480, 71, 23));
        pushButton_6 = new QPushButton(Widget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(600, 480, 71, 23));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(520, 290, 111, 81));
        radioButtonZufall = new QRadioButton(groupBox_2);
        radioButtonZufall->setObjectName(QStringLiteral("radioButtonZufall"));
        radioButtonZufall->setGeometry(QRect(10, 20, 82, 17));
        radioButtonZufall->setChecked(true);
        radioButtonKreis = new QRadioButton(groupBox_2);
        radioButtonKreis->setObjectName(QStringLiteral("radioButtonKreis"));
        radioButtonKreis->setGeometry(QRect(10, 40, 82, 17));
        radioButtonRaster = new QRadioButton(groupBox_2);
        radioButtonRaster->setObjectName(QStringLiteral("radioButtonRaster"));
        radioButtonRaster->setGeometry(QRect(10, 60, 82, 17));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pushButton->setText(QApplication::translate("Widget", "Neue St\303\244dte", 0));
        groupBox->setTitle(QApplication::translate("Widget", "Einstellungen", 0));
        label->setText(QApplication::translate("Widget", "St\303\244dte:", 0));
        spinBoxLocations->setPrefix(QString());
        label_2->setText(QApplication::translate("Widget", "Populationsgr\303\266\303\237e", 0));
        label_4->setText(QApplication::translate("Widget", "Mutationsrate", 0));
        doubleSpinBoxMutationrate->setPrefix(QString());
        doubleSpinBoxMutationrate->setSuffix(QApplication::translate("Widget", " %", 0));
        checkBoxReverse->setText(QApplication::translate("Widget", "Reverse", 0));
        checkBoxMultiThreading->setText(QApplication::translate("Widget", "Multithreading", 0));
        label_3->setText(QApplication::translate("Widget", "Threads", 0));
        pushButton_2->setText(QApplication::translate("Widget", "OK", 0));
        pushButton_7->setText(QApplication::translate("Widget", "OK", 0));
        pushButton_3->setText(QApplication::translate("Widget", "Neue Pop.", 0));
        pushButton_5->setText(QApplication::translate("Widget", "Start", 0));
        pushButton_6->setText(QApplication::translate("Widget", "Pause", 0));
        groupBox_2->setTitle(QApplication::translate("Widget", "Stadtgenerierung", 0));
        radioButtonZufall->setText(QApplication::translate("Widget", "Zuf\303\244llig", 0));
        radioButtonKreis->setText(QApplication::translate("Widget", "Kreisf\303\266rmig", 0));
        radioButtonRaster->setText(QApplication::translate("Widget", "Raster", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
