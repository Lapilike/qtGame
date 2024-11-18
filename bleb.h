#ifndef BLEB_H
#define BLEB_H
#include "enemy.h"
#include "player.h"

class Bleb : public QObject, public Enemy
{
    Q_OBJECT
private:
    QTimer *timer;
    int TriggerDistance;
    Obj* m_Attack;
public:
    Bleb(std::vector<std::vector<Tile>> *tiles, int TilePosX, int TilePosY, std::vector<int> *PlayerPos);
    bool isTriggered(std::vector<int> PlayerPos);
    void moveInPattern(std::vector<std::vector<Tile>> *tiles, std::vector<int> *PlayerPos);

    void Attack(std::vector<std::vector<Tile> > tiles, Player* player);
    void drawAttack(SpriteRenderer& renderer);
};

#endif // BLEB_H
