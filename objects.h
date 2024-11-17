#ifndef OBJECTS_H
#define OBJECTS_H
#define TILE_SIZE 64
#define MAP_HGHT 100
#define MAP_WDTH 100

class Object
{
    int x, y;
    char *TexturePath;

public:
    Object();
    Object(char *);
    void setPosition(int, int);
    void setTexture(char *);
    ~Object();
};

Object **Tile;

#endif //OBJECTS_H
