#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QOpenGLWidget>
#include "entity.h"
#include "inventory.h"
#include "enemy.h"

class Player : public QObject, public Entity
{
    Q_OBJECT
private:
    Stats m_Stats;
    Inventory m_Inv;
    Obj *m_Attack;
public:
    Player();
    void loadAnimations();

    void Attack(std::vector<std::vector<Tile> > tiles);
    int CalcDamage(Enemy *enemy);
    void drawAttack(SpriteRenderer &renderer);
    void setStats();
    int getStat(int StatType);

    void getDamaged(int Damage);
    void getTiles(std::vector<std::vector<int> > &NextTiles);
    void addItem(int ItemID, int ItemAmnt);
    void eqiupItem(int ItemID);
    Stats* getStats();

signals:
    void EnemyDied(Enemy* enemy);
};

#endif // PLAYER_H
