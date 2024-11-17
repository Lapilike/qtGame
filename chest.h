#ifndef CHEST_H
#define CHEST_H

#include "inventory.h"
#include "obj.h"
#include "tile.h"

class Chest : public Obj
{
public:
    Inventory m_inv;
    Chest();
    void spawnChest(std::vector<std::vector<Tile>> &Tiles,
                    int TilePosX,
                    int TilePosY,
                    std::vector<int> ItemsID);
};

#endif // CHEST_H
