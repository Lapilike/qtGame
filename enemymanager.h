#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "bleb.h"
#include "tile.h"
#include <QObject>

enum EnemyType {
    BLEB,
    SKELETON,
    ZOMBIE,
    BAT,
};

class EnemyManager : public QObject
{
    Q_OBJECT
private:
    SpriteRenderer *m_Renderer;
    std::map<EnemyType, std::vector<void*>> m_Enemies;
    int m_Wave;
    int m_EnemyAmnt;
public:
    EnemyManager(SpriteRenderer *Renderer);
    void spawnEnemies(std::vector<std::vector<Tile>> &tiles, Player *player);
    std::vector<void *> spawnBleb(std::vector<std::vector<Tile> > &tiles, Player* player);
    void CalcEnemyCount();

    void drawEnemies();
    bool isAllDead();
signals:
    void enemyDied(Enemy* enemy);
public slots:
    void enemyDeath(Enemy* enemy);
};

#endif // ENEMYMANAGER_H
