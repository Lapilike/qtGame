#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "stats.h"

#define ENEMY_ID_PATH "Data/IDs/EnemiesID.txt"

class Enemy : public Entity
{
private:
    Stats m_Stats;
    uintptr_t m_UID;
public:
    Enemy() {};
    virtual ~Enemy() {};
    void Spawn(std::vector<std::vector<Tile>> &Tiles, int EnemyID, int TilePosX, int TilePosY);
    void setStats(std::ifstream &EnemyID);
    void setEnemyAnimation(std::ifstream &IDFile, int AnimAmnt);
    void loadFromFile(int EnemyID);

    bool getDamaged(int Damage);
    bool isDead();

    int getStat(int StatType);
    int CalcDamage(Stats *AttackerStats);

    void setUID(uintptr_t UID);
    uintptr_t getUID();
};

#endif // ENEMY_H
