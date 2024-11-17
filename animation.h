#ifndef ANIMATION_H
#define ANIMATION_H
#include "spriterenderer.h"
enum EntityState {
    IDLE,
    IDLEUP,
    WALK,
    RUN,
    ATTACK,
};

class Animation
{
private:
    QOpenGLTexture* m_spriteSheet;
    int m_TotalFrames;
    int m_CurrentFrame;
    float m_AnimSpeed;
public:
    Animation() {};
    ~Animation() {
        m_spriteSheet->destroy();
        delete m_spriteSheet;
    };
    QOpenGLTexture* spriteSheet();
    void addAnimation(QImage spriteSheet, int FrameCount, float AnimSpeed);
    void addAnimation(std::string spriteSheet, int FrameCount, float AnimSpeed);
    bool increaseCurrFrame();
    int totalFrames();
    int currentFrame();
};

#endif // ANIMATION_H
