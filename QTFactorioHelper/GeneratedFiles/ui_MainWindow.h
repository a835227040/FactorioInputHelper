/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QLineEdit *textEdit;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(800, 27);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        MainWindowClass->setFont(font);
        MainWindowClass->setAcceptDrops(false);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8(":/MainWindow/D:/steam/steamapps/common/Factorio/data/base/graphics/icons/transport-belt.png")));
        MainWindowClass->setWindowIcon(icon);
        MainWindowClass->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QPalette palette;
        centralWidget->setPalette(palette);
        textEdit = new QLineEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 800, 27));
        MainWindowClass->setCentralWidget(centralWidget);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "FactorioInputHelper Ver 1.0.1 by leopard", nullptr));
        textEdit->setPlaceholderText(QCoreApplication::translate("MainWindowClass", "\347\233\264\346\216\245\350\276\223\345\205\245\344\270\255\346\226\207\345\271\266\346\214\211\344\270\213\345\233\236\350\275\246\357\274\214\345\215\263\345\217\257\345\217\221\351\200\201\343\200\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
