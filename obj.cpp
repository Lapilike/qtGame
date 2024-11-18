#include "obj.h"
#include "opengl.h"

Obj::Obj()
{
    texture = new QOpenGLTexture(QImage(TEST_TEX));
    Collision = nullptr;
    m_Pos = {200, 200};
    m_Size = {1, 1};
    m_Direct = {1, 0};
}

Obj::Obj(int Xpos, int Ypos)
{
    texture = new QOpenGLTexture(QImage(TEST_TEX));
    m_Pos = {Xpos, Ypos};
}

bool Obj::renderAnim(SpriteRenderer &renderer)
{
    renderer.drawSprite(*anim[IDLE]->spriteSheet(),
                        anim[IDLE]->currentFrame(),
                        anim[IDLE]->totalFrames(),
                        m_Pos,
                        m_Size,
                        m_Direct);
    if (anim[IDLE]->increaseCurrFrame())
        return true;

    return false;
}

bool Obj::renderAnim(SpriteRenderer &renderer, float angle)
{
    renderer.drawSprite(*anim[IDLE]->spriteSheet(),
                        anim[IDLE]->currentFrame(),
                        anim[IDLE]->totalFrames(),
                        angle,
                        m_Pos,
                        m_Size,
                        m_Direct);
    if (anim[IDLE]->increaseCurrFrame())
        return true;

    return false;
}

void Obj::setPosition(int Xpos, int Ypos)
{
    m_Pos[0] = Xpos;
    m_Pos[1] = Ypos;
}

void Obj::setSize(float Width, float Height)
{
    m_Size[0] = Width;
    m_Size[1] = Height;
}

void Obj::setDirection(float XDir, float YDir)
{
    m_Direct[0] = XDir;
    m_Direct[1] = YDir;
}

void Obj::setTexture(std::string TexturePath)
{
    texture = new QOpenGLTexture(QImage(TexturePath.data()).mirrored());
    texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Obj::addAnimation(std::string AnimationPath, int State, int FrameCount, float AnimSpeed)
{
    anim[(EntityState) State] = new Animation;
    anim[(EntityState) State]->addAnimation(AnimationPath, FrameCount, AnimSpeed);
}

void Obj::addAnimation(QImage SpriteSheet, int State, int FrameCount, float AnimSpeed)
{
    anim[(EntityState) State]->addAnimation(SpriteSheet, FrameCount, AnimSpeed);
}

void Obj::setNewCollision(float width, float height)
{
    Collision = new CollisionBox(&m_Pos);
    Collision->setSize(width, height);
}

void Obj::setCollision(float width, float height)
{
    Collision->setPositionVector(&m_Pos);
    Collision->setSize(width, height);
}

CollisionBox *Obj::getCollision()
{
    return Collision;
}

void Obj::draw(SpriteRenderer &renderer)
{
    std::vector<int> pos = {0, 0};
    pos[0] = m_Pos[0];
    pos[1] = m_Pos[1];
    renderer.drawSprite(*texture, pos, m_Size, m_Direct);
}

float Obj::x()
{
    float X;
    try {
        X = m_Pos.at(0);
    } catch (const std::out_of_range) {
        return 0;
    }
    return X;
}

float Obj::y()
{
    float Y;
    try {
        Y = m_Pos.at(1);
    } catch (const std::out_of_range) {
        return 0;
    }
    return Y;
}

Obj::~Obj() {}
