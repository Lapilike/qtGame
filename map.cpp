#include "map.h"
#include <fstream>
#include <sstream>

Map::Map(SpriteRenderer &renderer) {
    m_TileSet = new QOpenGLTexture(QImage(":/TileSets/Set1"));
    m_TileSet->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_TileSet->setMinificationFilter(QOpenGLTexture::Nearest);
    m_TileSet->setWrapMode(QOpenGLTexture::Repeat);
    m_width = 2;
    m_height = 2;
    m_TileMap ={
        {1, 2},
        {3, 4}
    };
    renderer.initMapRender(m_TileMap, m_width, m_height, 10, 10);
}

Map::Map(int w, int h) {
    m_width = w;
    m_height = h;
    tiles.resize(m_height);
    for(int i = 0; i < m_height; i++)
        tiles[i].resize(m_width);

}

Map::Map(SpriteRenderer &renderer, std::string FilePath, std::string TexturePath, int setWidth, int setHeight)
{
    m_TileSet = new QOpenGLTexture(QImage(TexturePath.data()));
    m_TileSet->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_TileSet->setMinificationFilter(QOpenGLTexture::Nearest);
    m_TileSet->setWrapMode(QOpenGLTexture::Repeat);
    loadFromFile(FilePath);
    renderer.initMapRender(m_TileMap, m_width, m_height, setHeight,  setWidth);
}


void Map::loadFromFile(std::string FilePath)
{
    std::ifstream file(FilePath);
    if(!file.is_open()) {
        qDebug() << "Error open file";
        return;
    }
    std::string line;
    std::getline(file, line);
    std::stringstream lineStream;
    lineStream << line;

    lineStream >> m_width;
    lineStream >> m_height;

    int value;
    std::vector<int> row;
    for(int i = 0; i < m_height; i++) {
        std::getline(file, line);
        lineStream.clear();
        lineStream << line;
        while(lineStream >> value)
            row.push_back(value);
        m_TileMap.push_back(row);
        row.clear();
    }


    for(int i = 0; i < m_height; i++) {
        std::vector<Tile> TileRow;
        std::getline(file, line);
        lineStream.clear();
        lineStream << line;
        while(lineStream >> value) {
            Tile *singleTile = new Tile;
            if(value == 1) {
                int Ypos = i * TILE_SIZE + TILE_SIZE/2;
                int Xpos = TileRow.size() * TILE_SIZE + TILE_SIZE/2;
                singleTile->block(Xpos, Ypos);
            }
            TileRow.push_back(*singleTile);
        }
        tiles.push_back(TileRow);
        row.clear();
    }
    file.close();
}

void Map::drawMap(SpriteRenderer &renderer)
{
    renderer.drawMap(*m_TileSet, {-1.0, -1.0}, m_width, m_height);
}

void Map::addChest(Chest *Chest)
{
    Chests.push_back(Chest);
}


