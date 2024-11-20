#ifndef ENTITY_H
#define ENTITY_H
#include "map.h"
#include "obj.h"
#include "stats.h"

class Entity : public Obj
{
private:
    EntityState m_State;
    int m_Vel;
    bool Staggered;

public:
    Entity();
    virtual ~Entity() {};
    bool checkCollision(std::vector<std::vector<Tile>> &tiles);
    void getTilesInFront(std::vector<std::vector<int>> &NextTiles);
    void move(std::vector<std::vector<Tile> > &tiles);
    void normalizeDir();
    void setVelocity(int);
    void setDirection(int, int);
    bool renderAnim(SpriteRenderer &renderer) override final;

    void setState(EntityState);
    EntityState getState();

    void stagger();
    void unStagger();
    bool isStaggered();
};

#endif // ENTITY_H
