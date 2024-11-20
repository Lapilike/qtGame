#ifndef BLEB_H
#define BLEB_H
#include "enemy.h"
#include "player.h"
#include "qtimer.h"

class Bleb : public QObject, public Enemy
{
    Q_OBJECT
private:
    QTimer *timer;
    int TriggerDistance;
    float m_AttackRange;
    Obj* m_Attack;
public:
    Bleb(std::vector<std::vector<Tile>> *tiles, int TilePosX, int TilePosY, Player *player);
    ~Bleb() {
        delete m_Attack;
        delete timer;
    };
    bool isTriggered(std::vector<int> PlayerPos);
    void moveInPattern(std::vector<std::vector<Tile>> *tiles, std::vector<int> &PlayerPos);

    void Attack(std::vector<std::vector<Tile> > &tiles, Player* player);
    void getTilesInRange(std::vector<std::vector<int>>& NextTiles);
    bool drawAttack(SpriteRenderer& renderer);
};

#endif // BLEB_H
