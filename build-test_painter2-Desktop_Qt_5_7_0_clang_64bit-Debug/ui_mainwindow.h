/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_file;
    QAction *actionNew;
    QAction *actionAdd_curve;
    QAction *actionModify;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuSave;
    QMenu *menuNew;
    QMenu *menuAdd;
    QMenu *menuModify;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 400);
        actionSave_file = new QAction(MainWindow);
        actionSave_file->setObjectName(QStringLiteral("actionSave_file"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionAdd_curve = new QAction(MainWindow);
        actionAdd_curve->setObjectName(QStringLiteral("actionAdd_curve"));
        actionModify = new QAction(MainWindow);
        actionModify->setObjectName(QStringLiteral("actionModify"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 22));
        menuSave = new QMenu(menuBar);
        menuSave->setObjectName(QStringLiteral("menuSave"));
        menuNew = new QMenu(menuBar);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuModify = new QMenu(menuBar);
        menuModify->setObjectName(QStringLiteral("menuModify"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuNew->menuAction());
        menuBar->addAction(menuAdd->menuAction());
        menuBar->addAction(menuModify->menuAction());
        menuBar->addAction(menuSave->menuAction());
        menuSave->addAction(actionSave_file);
        menuNew->addAction(actionNew);
        menuAdd->addAction(actionAdd_curve);
        menuModify->addAction(actionModify);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionAdd_curve);
        toolBar->addAction(actionModify);
        toolBar->addAction(actionSave_file);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSave_file->setText(QApplication::translate("MainWindow", "save", 0));
        actionNew->setText(QApplication::translate("MainWindow", "new", 0));
        actionAdd_curve->setText(QApplication::translate("MainWindow", "add curve", 0));
        actionModify->setText(QApplication::translate("MainWindow", "Select", 0));
        menuSave->setTitle(QApplication::translate("MainWindow", "Save", 0));
        menuNew->setTitle(QApplication::translate("MainWindow", "New", 0));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Add", 0));
        menuModify->setTitle(QApplication::translate("MainWindow", "Modify", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
