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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Image;
    QAction *actionNew;
    QAction *actionAdd_curve;
    QAction *actionModify;
    QAction *actionSave_file;
    QAction *actionOpen_file;
    QAction *actionOpen_image;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuSave;
    QMenu *menuNew;
    QMenu *menuAdd;
    QMenu *menuModify;
    QMenu *menuOpen;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 500);
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        QFont font;
        font.setFamily(QStringLiteral("Helvetica"));
        font.setPointSize(14);
        actionSave_Image->setFont(font);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setFont(font);
        actionAdd_curve = new QAction(MainWindow);
        actionAdd_curve->setObjectName(QStringLiteral("actionAdd_curve"));
        actionAdd_curve->setFont(font);
        actionModify = new QAction(MainWindow);
        actionModify->setObjectName(QStringLiteral("actionModify"));
        actionModify->setFont(font);
        actionSave_file = new QAction(MainWindow);
        actionSave_file->setObjectName(QStringLiteral("actionSave_file"));
        actionSave_file->setFont(font);
        actionOpen_file = new QAction(MainWindow);
        actionOpen_file->setObjectName(QStringLiteral("actionOpen_file"));
        actionOpen_file->setFont(font);
        actionOpen_image = new QAction(MainWindow);
        actionOpen_image->setObjectName(QStringLiteral("actionOpen_image"));
        actionOpen_image->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menuSave = new QMenu(menuBar);
        menuSave->setObjectName(QStringLiteral("menuSave"));
        menuNew = new QMenu(menuBar);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuModify = new QMenu(menuBar);
        menuModify->setObjectName(QStringLiteral("menuModify"));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuNew->menuAction());
        menuBar->addAction(menuAdd->menuAction());
        menuBar->addAction(menuModify->menuAction());
        menuBar->addAction(menuSave->menuAction());
        menuBar->addAction(menuOpen->menuAction());
        menuSave->addAction(actionSave_Image);
        menuSave->addSeparator();
        menuSave->addAction(actionSave_file);
        menuNew->addAction(actionNew);
        menuAdd->addAction(actionAdd_curve);
        menuModify->addAction(actionModify);
        menuOpen->addAction(actionOpen_file);
        menuOpen->addSeparator();
        menuOpen->addAction(actionOpen_image);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionAdd_curve);
        toolBar->addAction(actionModify);
        toolBar->addAction(actionSave_Image);
        toolBar->addAction(actionSave_file);
        toolBar->addAction(actionOpen_file);
        toolBar->addAction(actionOpen_image);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSave_Image->setText(QApplication::translate("MainWindow", "Save Image", 0));
        actionNew->setText(QApplication::translate("MainWindow", "new", 0));
        actionAdd_curve->setText(QApplication::translate("MainWindow", "add curve", 0));
        actionModify->setText(QApplication::translate("MainWindow", "Select", 0));
        actionSave_file->setText(QApplication::translate("MainWindow", "Save file", 0));
        actionOpen_file->setText(QApplication::translate("MainWindow", "open file", 0));
        actionOpen_image->setText(QApplication::translate("MainWindow", "open image", 0));
        menuSave->setTitle(QApplication::translate("MainWindow", "Save", 0));
        menuNew->setTitle(QApplication::translate("MainWindow", "New", 0));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Add", 0));
        menuModify->setTitle(QApplication::translate("MainWindow", "Modify", 0));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
