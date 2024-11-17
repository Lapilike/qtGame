/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "graphics.h"

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *centralwidget;
    OpenGL *openGLWidget;
    QPushButton *pushButton_2;
    QFrame *frame;
    QListView *listView;
    QListView *listView_2;
    QLabel *label;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameWindow->sizePolicy().hasHeightForWidth());
        GameWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName("centralwidget");
        openGLWidget = new OpenGL(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setEnabled(true);
        openGLWidget->setGeometry(QRect(0, 0, 341, 231));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(960, 540, 71, 81));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(370, 80, 841, 451));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        listView = new QListView(frame);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(0, 60, 411, 391));
        listView->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        listView_2 = new QListView(frame);
        listView_2->setObjectName("listView_2");
        listView_2->setGeometry(QRect(430, 60, 411, 391));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 10, 131, 41));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        GameWindow->setCentralWidget(centralwidget);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "GameWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GameWindow", "Close", nullptr));
        label->setText(QCoreApplication::translate("GameWindow", "Inventory", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
