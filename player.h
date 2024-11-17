#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "inventory.h"
#include <QKeyEvent>
#include <QOpenGLWidget>


class Player : public Entity
{
private:
    Stats m_Stats;
    Inventory m_Inv;
    Obj* m_Attack;
public:
    Player();
    void Attack(std::vector<std::vector<Tile> > tiles);
    void drawAttack(SpriteRenderer& renderer);
    void setStats();
};

#endif // PLAYER_H
