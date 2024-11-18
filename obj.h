#ifndef OBJ_H
#define OBJ_H
#include <QOpenGLTexture>
#include <QWidget>
#include "animation.h"
#include "collisionbox.h"
#include "spriterenderer.h"
#define TILE_SIZE 60

enum InteractionType { NOINTERACTION, CHEST, NPC, DIALOG, SHOP, ENEMY };

class Obj
{
private:
    CollisionBox *Collision;

public:
    std::vector<int> m_Pos;
    std::vector<float> m_Size;
    std::vector<float> m_Direct;
    QOpenGLTexture *texture;
    std::map<EntityState, Animation *> anim;

    Obj();
    Obj(int Xpos, int Ypos);
    virtual bool renderAnim(SpriteRenderer &renderer);
    virtual bool renderAnim(SpriteRenderer &renderer, float angle);
    void draw(SpriteRenderer &renderer);
    void setPosition(int Xpos, int Ypos);
    void setSize(float Width, float Height);
    void setDirection(float XDir, float YDir);
    void setTexture(std::string TexturePath);

    void addAnimation(std::string AnimationPath, int State, int FrameCount, float AnimSpeed);
    void addAnimation(QImage SpriteSheet, int State, int FrameCount, float AnimSpeed);

    void setNewCollision(float width, float height);
    void setCollision(float width, float height);
    CollisionBox *getCollision();
    float x();
    float y();
    ~Obj();
};

#endif // OBJ_H
