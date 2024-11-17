#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <iostream>
#include <QTimer>
#include <QLabel>
#include <QImage>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    QTimer::singleShot(0, this, SLOT(showFullScreen()));
    ui->setupUi(this);
    move(0, 0);
    ui->frame->setVisible(false);
    connect(ui->openGLWidget, &OpenGL::openChest, this, &GameWindow::openInventory);
    ui->openGLWidget->resize(width() / 1.25f, height() / 1.25f);
    std::cout << width() << " " << height() << " " << std::endl;
    ui->openGLWidget->move(0, 0);
    ui->openGLWidget->show();
    ui->openGLWidget->setFocus();


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::openInventory(Chest& chest)
{
    if(ui->frame->isVisible())
        return;
    for(int i = 0; i < chest.m_inv.getItemAmnt(); i++) {
        QListWidgetItem *ListItem = new QListWidgetItem;
        ListItem->setText(chest.m_inv.getItemName(i).data());
        ui->listWidget_2->addItem(ListItem);
    }
    ui->frame->setVisible(true);
}



void GameWindow::on_pushButton_clicked()
{
    ui->openGLWidget->setVisible(true);
}


void GameWindow::on_pushButton_2_clicked()
{
    close();
}


void GameWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{

}

