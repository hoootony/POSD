/********************************************************************************
** Form generated from reading UI file 'GraphicalUI.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICALUI_H
#define UI_GRAPHICALUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MindMapClass
{
public:
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionInsert_a_Child;
    QAction *actionInsert_a_Parent;
    QAction *actionInsert_a_Sibling;
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MindMapClass)
    {
        if (MindMapClass->objectName().isEmpty())
            MindMapClass->setObjectName(QStringLiteral("MindMapClass"));
        MindMapClass->resize(800, 600);
        actionEdit = new QAction(MindMapClass);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/icon/pencil41.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon);
        actionDelete = new QAction(MindMapClass);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/icon/delete96.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon1);
        actionInsert_a_Child = new QAction(MindMapClass);
        actionInsert_a_Child->setObjectName(QStringLiteral("actionInsert_a_Child"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/icon/round77.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert_a_Child->setIcon(icon2);
        actionInsert_a_Parent = new QAction(MindMapClass);
        actionInsert_a_Parent->setObjectName(QStringLiteral("actionInsert_a_Parent"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/icon/rounded54.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert_a_Parent->setIcon(icon3);
        actionInsert_a_Sibling = new QAction(MindMapClass);
        actionInsert_a_Sibling->setObjectName(QStringLiteral("actionInsert_a_Sibling"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/icon/square181.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert_a_Sibling->setIcon(icon4);
        actionNew = new QAction(MindMapClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("Resources/icon/add26.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon5);
        actionLoad = new QAction(MindMapClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("Resources/icon/folder232.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon6);
        actionSave = new QAction(MindMapClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("Resources/icon/floppy1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon7);
        actionAbout = new QAction(MindMapClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(MindMapClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCut = new QAction(MindMapClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("Resources/icon/scissors9.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon8);
        actionCopy = new QAction(MindMapClass);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon9;
        icon9.addFile(QStringLiteral("Resources/icon/copy8.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon9);
        actionPaste = new QAction(MindMapClass);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        QIcon icon10;
        icon10.addFile(QStringLiteral("Resources/icon/clipboard46.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon10);
        centralWidget = new QWidget(MindMapClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MindMapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MindMapClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MindMapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MindMapClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MindMapClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MindMapClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MindMapClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionEdit);
        menuEdit->addAction(actionDelete);
        menuEdit->addAction(actionInsert_a_Child);
        menuEdit->addAction(actionInsert_a_Sibling);
        menuEdit->addAction(actionInsert_a_Parent);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionLoad);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCut);
        mainToolBar->addAction(actionCopy);
        mainToolBar->addAction(actionPaste);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionEdit);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionInsert_a_Child);
        mainToolBar->addAction(actionInsert_a_Sibling);
        mainToolBar->addAction(actionInsert_a_Parent);

        retranslateUi(MindMapClass);

        QMetaObject::connectSlotsByName(MindMapClass);
    } // setupUi

    void retranslateUi(QMainWindow *MindMapClass)
    {
        MindMapClass->setWindowTitle(QApplication::translate("MindMapClass", "MindMap", 0));
        actionEdit->setText(QApplication::translate("MindMapClass", "Edit", 0));
        actionEdit->setShortcut(QApplication::translate("MindMapClass", "E", 0));
        actionDelete->setText(QApplication::translate("MindMapClass", "Delete", 0));
        actionDelete->setShortcut(QApplication::translate("MindMapClass", "D", 0));
        actionInsert_a_Child->setText(QApplication::translate("MindMapClass", "Insert a Child", 0));
        actionInsert_a_Child->setShortcut(QApplication::translate("MindMapClass", "C", 0));
        actionInsert_a_Parent->setText(QApplication::translate("MindMapClass", "Insert a Parent", 0));
        actionInsert_a_Parent->setShortcut(QApplication::translate("MindMapClass", "P", 0));
        actionInsert_a_Sibling->setText(QApplication::translate("MindMapClass", "Insert a Sibling", 0));
        actionInsert_a_Sibling->setShortcut(QApplication::translate("MindMapClass", "S", 0));
        actionNew->setText(QApplication::translate("MindMapClass", "Create a new mind map", 0));
        actionNew->setShortcut(QApplication::translate("MindMapClass", "C", 0));
        actionLoad->setText(QApplication::translate("MindMapClass", "Open a mind map", 0));
        actionLoad->setShortcut(QApplication::translate("MindMapClass", "O", 0));
        actionSave->setText(QApplication::translate("MindMapClass", "Save a mind map", 0));
        actionSave->setShortcut(QApplication::translate("MindMapClass", "S", 0));
        actionAbout->setText(QApplication::translate("MindMapClass", "About", 0));
        actionAbout->setShortcut(QApplication::translate("MindMapClass", "A", 0));
        actionExit->setText(QApplication::translate("MindMapClass", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MindMapClass", "E", 0));
        actionCut->setText(QApplication::translate("MindMapClass", "Cut", 0));
        actionCopy->setText(QApplication::translate("MindMapClass", "Copy", 0));
        actionPaste->setText(QApplication::translate("MindMapClass", "Paste", 0));
        menuFile->setTitle(QApplication::translate("MindMapClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("MindMapClass", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("MindMapClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MindMapClass: public Ui_MindMapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICALUI_H
