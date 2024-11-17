#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "stats.h"

#define ENEMY_ID_PATH "Data/IDs/EnemiesID.txt"

class Enemy : public Entity
{
private:
    Stats m_Stats;

public:
    Enemy();
    ~Enemy();
    void Spawn(std::vector<std::vector<Tile>> &Tiles, int EnemyID, int TilePosX, int TilePosY);
    void setStats(std::ifstream &EnemyID);
    void setEnemyAnimation(std::ifstream &IDFile, int AnimAmnt);
    void loadFromFile(int EnemyID);

    void getDamaged(int Damage);
    bool isDead();
};

#endif // ENEMY_H
