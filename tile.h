#ifndef TILE_H
#define TILE_H
#include "obj.h"

class Tile
{
private:
    bool m_Blocked;
    CollisionBox *m_Collision;
    InteractionType m_Interaction;
    std::vector<int> m_Pos;
    void *m_Object;

public:
    Tile();
    bool isBlocked();
    void block(int Xpos, int Ypos);
    CollisionBox *getCollision();
    void setObject(Obj *ObjectPtr, InteractionType Interaction);
    void *getObject();
    InteractionType Interation();
};

#endif // TILE_H
