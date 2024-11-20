#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include "chest.h"

#define SCR_WDTH 1920
#define SCR_HGHT 1080

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void openInventory(Chest &chest);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void showCountDown();

private:
    Ui::GameWindow *ui;
};
#endif // GAMEWINDOW_H
