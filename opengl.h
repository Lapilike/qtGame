#ifndef OPENGL_H
#define OPENGL_H

#include "enemymanager.h"
#define VRTX_CNT 8
#define FPS 60.0f
#define TEST_TEX (":/Textures/Test")

#include <QOpenGLFunctions>
#include <QSet>
#include <QTimer>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "animation.h"
#include "bleb.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "spriterenderer.h"

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    Map *m_level;
    Player* m_player;
    SpriteRenderer* m_Renderer;
    std::vector<QOpenGLTexture*> m_textures;
    std::map<std::string, std::map<EntityState, Animation*>> m_Animations;
    QSet<int> m_PressedKeys;
    QTimer *timer;

    std::map<EntityState, Animation*> anim;
    EnemyManager* m_Manager;

public:
    OpenGL(QWidget *parent = nullptr)
        : QOpenGLWidget(parent)
    {
        m_player = new Player;
        m_level = new Map(10, 10);
    }
    ~OpenGL()
    {
        delete m_player;
        delete m_level;
        delete m_Renderer;
        for (int i = 0; i < m_textures.size(); i++) {
            m_textures[i]->destroy();
            delete m_textures[i];
        }
        m_textures.clear();
    }
signals:
    void openChest(Chest &chest);
    void startCountDown();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QOpenGLShaderProgram *loadShader();
    void initMap();
    void drawMap();
    void drawPlayer();
    void drawEnemies();
    void loadTextures();
    void checkMoveKeys();
    void checkInteractKeys();
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void checkDeadEnemies();

public slots:
    void updateGame();
    void deleteEnemy(Enemy* enemy);
};

#endif // OPENGL_H
