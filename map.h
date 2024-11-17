#ifndef MAP_H
#define MAP_H
#include <vector>
#include "tile.h"
#include "chest.h"

class Map
{
private:
    int m_width;
    int m_height;
    std::vector<std::vector<int>> m_TileMap;
    QOpenGLTexture* m_TileSet;
public:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Chest*> Chests;
    Map(SpriteRenderer &renderer);
    Map(int, int);
    Map(SpriteRenderer &renderer, std::string FilePath, std::string TexturePath, int setWidth, int setHeight);
    void loadFromFile(std::string FilePath);
    void drawMap(SpriteRenderer & renderer);
    void addChest(Chest* Chest);
};

#endif // MAP_H
