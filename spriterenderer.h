#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>

#define VERTEX_SHADER ":/Shaders/vertexShader.vert"
#define FRAGMENT_SHADER ":/Shaders/fragShader.frag"

class SpriteRenderer
{
private:
    QOpenGLShaderProgram *m_shader;
    QOpenGLBuffer m_VBO, m_MapVBO, m_MapEBO;
    QOpenGLVertexArrayObject m_VAO, m_TileSetVAO;

public:
    SpriteRenderer(QOpenGLShaderProgram *);
    ~SpriteRenderer()
    {
        m_VBO.destroy();
        m_VAO.destroy();
        m_MapVBO.destroy();
    }
    std::vector<float> normalizeVec(std::vector<float> vector);
    void initMapRender(
        std::vector<std::vector<int>> TileIDs, int Width, int Height, int SetHeight, int SetWidth);
    void initRenderer();
    void drawMap(QOpenGLTexture &TileSet, std::vector<float> position, int mapWidth, int mapHeight);
    void drawSprite(QOpenGLTexture &texture,
                    int CurrentFrame,
                    float TotalFrames,
                    std::vector<int> position,
                    std::vector<float> size,
                    std::vector<float> direction);
    void drawSprite(QOpenGLTexture &texture,
                    std::vector<int> position,
                    std::vector<float> size,
                    std::vector<float> direction);
    void drawSprite(QOpenGLTexture &texture,
                    int CurrentFrame,
                    float TotalFrames,
                    int angle,
                    std::vector<int> position,
                    std::vector<float> size,
                    std::vector<float> direction);
};

#endif // SPRITERENDERER_H
