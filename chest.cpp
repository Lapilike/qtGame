#include "chest.h"
#include "opengl.h"

Chest::Chest() : Obj() {}

void Chest::spawnChest(std::vector<std::vector<Tile>>& Tiles, int TilePosX, int TilePosY, std::vector<int> ItemsID)
{
    try {
        Tiles.at(TilePosY).at(TilePosX);
    } catch (const std::out_of_range) {
        return;
    }

    Tiles[TilePosY][TilePosX].setObject(this, CHEST);
    m_Pos[0] = TILE_SIZE * (TilePosX + 0.5f);
    m_Pos[1] = TILE_SIZE * (TilePosY + 0.5f);
    setNewCollision(30, 22.5f);
    setTexture(":/Textures/Chest");
    for(int i = 0; i < ItemsID.size(); i++) {
        Item* item = new Item(ItemsID[i]);
        m_inv.addItem(item);
    }
};
