#ifndef ENTITY_H
#define ENTITY_H
#include "obj.h"
#include "map.h"
#include "stats.h"

class Entity : public Obj
{
private:
    EntityState m_State;
    int m_Vel;
    bool Staggered;
public:
    Entity();
    std::vector<bool> checkIntersect(std::vector<float> tile);
    bool checkCollision(std::vector<std::vector<Tile>> tiles);
    void getTilesInFront(std::vector<std::vector<int> > &NextTiles);
    void move(std::vector<std::vector<Tile>> tiles);
    void normalizeDir();
    void setVelocity(int);
    void setDirection(int, int);
    bool renderAnim(SpriteRenderer & renderer) override;

    void setState(EntityState);
    EntityState getState();

    void stagger();
    void unStagger();
    bool isStaggered();
};

#endif // ENTITY_H
