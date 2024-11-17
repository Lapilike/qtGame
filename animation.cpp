#include "animation.h"

void Animation::addAnimation(QImage spriteSheet, int FrameCount, float AnimSpeed)
{
    m_spriteSheet = new QOpenGLTexture(spriteSheet.mirrored());
    m_spriteSheet->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_spriteSheet->setMinificationFilter(QOpenGLTexture::Nearest);
    m_spriteSheet->setWrapMode(QOpenGLTexture::Repeat);
    m_TotalFrames = FrameCount;
    m_AnimSpeed = AnimSpeed;
    m_CurrentFrame = 0;
}

void Animation::addAnimation(std::string AnimationPath, int FrameCount, float AnimSpeed)
{
    m_spriteSheet = new QOpenGLTexture(QImage(AnimationPath.data()).mirrored());
    m_spriteSheet->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_spriteSheet->setMinificationFilter(QOpenGLTexture::Nearest);
    m_spriteSheet->setWrapMode(QOpenGLTexture::Repeat);
    m_TotalFrames = FrameCount;
    m_AnimSpeed = AnimSpeed;
    m_CurrentFrame = 0;
}

bool Animation::increaseCurrFrame()
{
    m_CurrentFrame++;
    if(m_CurrentFrame == m_TotalFrames * m_AnimSpeed) {
        m_CurrentFrame = 0;
        return true;
    }
    return false;
}

QOpenGLTexture* Animation::spriteSheet() {
    return m_spriteSheet;
}

int Animation::totalFrames() {
    return m_TotalFrames;
}

int Animation::currentFrame() {
    return m_CurrentFrame / m_AnimSpeed;
}
