#ifndef OPENGL_H
#define OPENGL_H

#define VRTX_CNT 8
#define FPS 60.0f
#define TEST_TEX (":/Textures/Test")

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSet>
#include <QTimer>

#include "spriterenderer.h"
#include "map.h"
#include "player.h"
#include "animation.h"
#include "enemy.h"

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions {

    Q_OBJECT

private:

    Map* m_level;
    Obj m_Object;
    Player* m_player;
    std::vector<Enemy*> Enemies;
    SpriteRenderer* m_Renderer;
    std::vector<QOpenGLTexture*> m_textures;
    std::map<std::string, std::map<EntityState, Animation*>> m_Animations;
    QSet<int> m_PressedKeys;
    QTimer *timer;

    Obj* Square;
    float angle;
public:
    OpenGL (QWidget* parent = nullptr)
        : QOpenGLWidget(parent)
    {
        m_player = new Player;
        m_level = new Map(10, 10);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &OpenGL::updateGame);
        timer->start(1000/FPS);
    }
    ~OpenGL() {
        delete m_player;
        delete m_level;
        delete m_Renderer;
        for(int i = 0; i < m_textures.size(); i++) {
            m_textures[i]->destroy();
            delete m_textures[i];
        }
        m_textures.clear();
    }
signals:
    void openChest(Chest& chest);

protected:   
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QOpenGLShaderProgram* loadShader();
    void initMap();
    void drawMap();
    void drawPlayer();
    void loadTextures();
    void checkMoveKeys();
    void checkInteractKeys();
    void keyPressEvent(QKeyEvent* ) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    //sadasdasdasd
    //sadasdsadsadas
    //sadsadasdasdas
    void checkDeadEnemies();

public slots:
    void updateGame();

};

#endif // OPENGL_H
