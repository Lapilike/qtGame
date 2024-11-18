#include "spriterenderer.h"
#include <QMatrix2x2>
#include "opengl.h"
#include <cmath>

SpriteRenderer::SpriteRenderer(QOpenGLShaderProgram *program)
    : m_MapEBO(QOpenGLBuffer::IndexBuffer)
{
    QMatrix4x4 projection;
    projection.ortho(0.0f, 1920, 0.0f, 1080, -1.0f, 1.0f);

    this->m_shader = program;

    m_shader->bind();
    m_shader->setUniformValue("projection", projection);
    m_shader->release();

    initRenderer();
}

std::vector<float> SpriteRenderer::normalizeVec(std::vector<float> vector)
{
    std::vector<float> normalized = {0, 0};
    float absolute = sqrt(pow(vector[0], 2) + pow(vector[1], 2));
    normalized[0] = vector[0] / absolute;
    normalized[1] = vector[1] / absolute;
    return normalized;
}

void SpriteRenderer::initMapRender(std::vector<std::vector<int>> TileIDs,
                                   int Width,
                                   int Height,
                                   int SetHeight,
                                   int SetWidth)
{
    std::vector<float> vertecies;
    std::vector<unsigned int> indicies;
    unsigned int currIndex = 0;
    float XPos = 0;
    float YPos = 0;
    float TexXPos = 0;
    float TexYPos = 0;
    float TileTexSizeX = 1.0f / (float) SetWidth;
    float TileTexSizeY = 1.0f / (float) SetHeight;
    for (int i = 0; i < Height; i++) {
        for (int k = 0; k < Width; k++) {
            XPos = (TILE_SIZE * (float) k);
            YPos = (TILE_SIZE * (float) i);
            TexXPos = (float) (TileIDs[i][k] % SetWidth) * TileTexSizeX;
            TexYPos = (float) (TileIDs[i][k] / SetHeight) * TileTexSizeY;

            vertecies.insert(vertecies.end(),
                             {XPos,
                              YPos,
                              TexXPos,
                              TexYPos,
                              XPos + TILE_SIZE,
                              YPos,
                              TexXPos + TileTexSizeX,
                              TexYPos,
                              XPos + TILE_SIZE,
                              YPos + TILE_SIZE,
                              TexXPos + TileTexSizeX,
                              TexYPos + TileTexSizeY,
                              XPos,
                              YPos + TILE_SIZE,
                              TexXPos,
                              TexYPos + TileTexSizeY});

            indicies.insert(indicies.end(),
                            {currIndex,
                             currIndex + 1,
                             currIndex + 2,
                             currIndex,
                             currIndex + 2,
                             currIndex + 3});

            currIndex += 4;
        }
    }
    m_MapVBO.create();
    m_MapVBO.bind();
    m_MapVBO.allocate(vertecies.data(), vertecies.size() * sizeof(float));
    m_MapVBO.release();

    m_MapEBO.create();
    m_MapEBO.bind();
    m_MapEBO.allocate(indicies.data(), indicies.size() * sizeof(unsigned int));
    m_MapEBO.release();

    m_TileSetVAO.create();
    m_TileSetVAO.bind();
    m_MapVBO.bind();
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(float));

    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(float), 2, 4 * sizeof(float));

    m_MapEBO.bind();
    m_TileSetVAO.release();
}

void SpriteRenderer::initRenderer()
{
    float x = static_cast<int>(TILE_SIZE / 2);
    float ObjectMatrix[] = {
        -x,
        -x,
        0,
        0,
        -x,
        x,
        0,
        1,
        x,
        x,
        1,
        1,
        x,
        -x,
        1,
        0,
    };
    m_VAO.create();
    m_VBO.create();
    m_VBO.bind();
    m_VBO.allocate(ObjectMatrix, 16 * sizeof(float));
    m_VBO.release();
    m_shader->release();

    m_VAO.bind();
    m_VBO.bind();
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(float));

    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(float), 2, 4 * sizeof(float));

    m_VAO.release();
}

void SpriteRenderer::drawMap(QOpenGLTexture &TileSet,
                             std::vector<float> position,
                             int mapWidth,
                             int mapHeight)
{
    QMatrix4x4 textMat;
    textMat.setToIdentity();
    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(position[0], position[1]);

    m_shader->bind();
    TileSet.bind(0);
    m_shader->setUniformValue("texture1", 0);
    m_shader->setUniformValue("model", model);
    m_shader->setUniformValue("textMat", textMat);

    m_TileSetVAO.bind();
    glDrawElements(GL_TRIANGLES, mapHeight * mapWidth * 6, GL_UNSIGNED_INT, nullptr);
    m_TileSetVAO.release();
    TileSet.release();
    m_shader->release();
}

void SpriteRenderer::drawSprite(QOpenGLTexture& texture,
                                int CurrentFrame,
                                float TotalFrames,
                                std::vector<int> position,
                                std::vector<float> size,
                                std::vector<float> direction) {
    QMatrix4x4 TexMat;
    TexMat.setToIdentity();
    TexMat.scale(1.0 / TotalFrames, 1.0, 1.0);
    TexMat.translate(CurrentFrame, 0);

    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(position[0], position[1]);
    if (direction[0] != 0)
        model.scale(direction[0], 1, 1);
    if (direction[1] != 0)
        model.scale(1, abs(direction[1]), 1);
    model.scale(size[0], size[1]);

    m_shader->bind();
    texture.bind(0);
    m_shader->setUniformValue("texture1", 0);
    m_shader->setUniformValue("model", model);
    m_shader->setUniformValue("textMat", TexMat);

    m_VAO.bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    m_VAO.release();
    texture.release();
    m_shader->release();
}

void SpriteRenderer::drawSprite(QOpenGLTexture& texture,
                                int CurrentFrame,
                                float TotalFrames,
                                int angle,
                                std::vector<int> position,
                                std::vector<float> size,
                                std::vector<float> direction) {
    QMatrix4x4 TexMat;
    TexMat.setToIdentity();
    TexMat.scale(1.0 / TotalFrames, 1.0, 1.0);

    TexMat.translate(CurrentFrame, 0);

    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(position[0], position[1]);
    model.rotate(angle, 0, 0, 1);
    if (direction[0] != 0)
        model.scale(direction[0], 1, 1);
    if (direction[1] != 0)
        model.scale(1, abs(direction[1]), 1);
    model.scale(size[0], size[1]);

    m_shader->bind();
    texture.bind(0);
    m_shader->setUniformValue("texture1", 0);
    m_shader->setUniformValue("model", model);
    m_shader->setUniformValue("textMat", TexMat);

    m_VAO.bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    m_VAO.release();
    texture.release();
    m_shader->release();
}

void SpriteRenderer::drawSprite(QOpenGLTexture& texture,
                                std::vector<int> position,
                                std::vector<float> size,
                                std::vector<float> direction) {
    float angle = (atan(direction[1]/direction[0])) / M_PI * 180;
    QMatrix4x4 TextMat;
    TextMat.setToIdentity();
    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(position[0], position[1]);
    model.scale(size[0], size[1]);
    model.rotate(angle, 0, 0, 1);

    m_shader->bind();
    texture.bind(0);
    m_shader->setUniformValue("texture1", 0);
    m_shader->setUniformValue("model", model);
    m_shader->setUniformValue("textMat", TextMat);

    m_VAO.bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    m_VAO.release();
    texture.release();
    m_shader->release();
}
