#include "objects.h"
#define PATH ":/Textures/Floor/Floor_Brick"

void generateMap() {
    Tile = new Object*[MAP_HGHT];
    for(int i = 0; i < MAP_WDTH; i++)
        Tile[i] = new Object[MAP_WDTH];

    for(int i = 0; i < MAP_HGHT; i++) {
        for(int k = 0; k < MAP_WDTH; k++) {
            Tile[i][k].setPosition(k * TILE_SIZE, i * TILE_SIZE);
            Tile[i][k].setTexture(PATH);
        }
    }
}
