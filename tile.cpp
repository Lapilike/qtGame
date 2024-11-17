#include "tile.h"

Tile::Tile() {
    m_Blocked = false;
    m_Object = nullptr;
    m_Interaction = NOINTERACTION;
    m_Collision = nullptr;
    m_Pos = {0, 0};
}

bool Tile::isBlocked() {
    return m_Blocked;
}

void Tile::block(int Xpos, int Ypos)
{
    m_Collision = new CollisionBox(&m_Pos);
    m_Collision->setSize(TILE_SIZE/2, TILE_SIZE/2);

    m_Pos = {Xpos, Ypos};
    m_Blocked = true;
}

CollisionBox* Tile::getCollision()
{
    return m_Collision;
}

void Tile::setObject(Obj *ObjectPtr, InteractionType Interaction)
{
    m_Object = ObjectPtr;
    m_Interaction = Interaction;
}

void *Tile::getObject()
{
    return m_Object;
}

InteractionType Tile::Interation()
{
    return m_Interaction;
}



