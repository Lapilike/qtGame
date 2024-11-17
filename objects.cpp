#include "objects.h"
#include <string.h>

Object::Object(char *Path)
{
    x = y = 0;
    TexturePath = new char[strlen(Path)];
    strcpy(TexturePath, Path);
}

void Object::setPosition(int Xpos, int Ypos)
{
    x = Xpos;
    y = Ypos;
}
void Object::setTexture(char *Path)
{
    strcpy(TexturePath, Path);
}

Object::Object()
{
    x = y = 0;
}

Object::~Object() {}
