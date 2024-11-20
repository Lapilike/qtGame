#include "opengl.h"

#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "chest.h"

void OpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0.5, 0.5, 255);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1920, 0, 1080, -1, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_Renderer = new SpriteRenderer(loadShader());
    initMap();
    loadTextures();
    m_player->anim = anim;
    m_level->tiles[m_player->m_Pos[1] / TILE_SIZE][m_player->m_Pos[0] / TILE_SIZE].setObject(m_player, PLAYER);

    m_Manager = new EnemyManager(m_Renderer);
    m_Manager->spawnEnemies(m_level->tiles, m_player);

    connect(m_player, &Player::EnemyDied, m_Manager, &EnemyManager::enemyDeath);
    connect(m_Manager, &EnemyManager::enemyDied, this, &OpenGL::deleteEnemy);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        static bool isRunning = false;

        if (isRunning) return;
        isRunning = true;

        QElapsedTimer elapsedTimer;
        elapsedTimer.start();
        updateGame();
        int elapsed = elapsedTimer.elapsed();
        int nextInterval = fmax(0, static_cast<int>(1000/FPS) - static_cast<int>(elapsed));
        timer->setInterval(nextInterval);
        isRunning = false;
    });
    timer->start(1000/FPS);
}

void OpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}


void OpenGL::paintGL() {
    drawMap();
    m_Manager->drawEnemies();
    drawPlayer();
}

QOpenGLShaderProgram *OpenGL::loadShader()
{
    QOpenGLShaderProgram *shader = new QOpenGLShaderProgram;
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Vertex, VERTEX_SHADER))
        return nullptr;
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Fragment, FRAGMENT_SHADER))
        return nullptr;
    if (!shader->link())
        return nullptr;
    return shader;
}

void OpenGL::initMap()
{
    m_level = new Map(*m_Renderer, "Data\\Maps\\level1.txt", ":/TileSets/Set1", 10, 10);
    Chest *chest = new Chest();
    chest->spawnChest(m_level->tiles, 5, 5, {0, 1});
    m_level->addChest(chest);
}


void OpenGL::updateGame() {
    if(!m_player->isStaggered()) {
        checkMoveKeys();
        checkInteractKeys();
    }
    if(m_Manager->isAllDead()) {
        QTimer::singleShot(5000, [=]() { m_Manager->spawnEnemies(m_level->tiles, m_player); });
        emit startCountDown();
    }
    update();
}

void OpenGL::deleteEnemy(Enemy *enemy)
{
    int TilePosX = enemy->m_Pos[0] / TILE_SIZE;
    int TilePosY = enemy->m_Pos[1] / TILE_SIZE;
    m_level->tiles[TilePosY][TilePosX].setObject(nullptr, NOINTERACTION);
    delete enemy;
}

void OpenGL::loadTextures()
{
    m_textures.resize(4);
    m_textures[0] = new QOpenGLTexture(QImage(TEST_TEX).mirrored());
    m_textures[1] = new QOpenGLTexture(QImage(":/Textures/Player").mirrored());
    m_textures[2] = new QOpenGLTexture(QImage(":/Textures/Floor_Brick").mirrored());
    m_textures[3] = new QOpenGLTexture(QImage(":/Textures/Chest").mirrored());

    for (int i = 0; i < m_textures.size(); i++) {
        m_textures[i]->setMagnificationFilter(QOpenGLTexture::Nearest);
        m_textures[i]->setMinificationFilter(QOpenGLTexture::Nearest);
        m_textures[i]->setWrapMode(QOpenGLTexture::Repeat);
    }


    anim[IDLE] = new Animation;
    anim[IDLE]->addAnimation(":/Animations/Player/Player_Idle", 6, 8);
    anim[IDLEUP] = new Animation;
    anim[IDLEUP]->addAnimation(QImage(":/Animations/Player/Player_Idle_Up"), 6, 8);
    anim[RUN] = new Animation;
    anim[RUN]->addAnimation(QImage(":/Animations/Player/Player_Run"), 4, 3);
    anim[ATTACK] = new Animation;
    anim[ATTACK]->addAnimation(QImage(":/Animations/Player/Player_Attack"), 8, 2);
}

void OpenGL::drawMap()
{
    m_level->drawMap(*m_Renderer);
    for (int i = 0; i < m_level->Chests.size(); i++)
        m_level->Chests[i]->draw(*m_Renderer);
}

void OpenGL::drawPlayer()
{
    if (m_player->getState() == ATTACK) {
        m_player->drawAttack(*m_Renderer);
    }
    if (m_player->renderAnim(*m_Renderer) && m_player->getState() == ATTACK) {
        m_player->unStagger();
    }
}

void OpenGL::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) // Игнорируем повторные события при удержании клавиши
        m_PressedKeys.insert(event->nativeScanCode()); // Добавляем клавишу в набор нажатых клавиш
}

void OpenGL::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) { // Игнорируем повторные события при удержании клавиши
        m_PressedKeys.remove(event->nativeScanCode()); // Добавляем клавишу в набор нажатых клавиш
    }
}

void OpenGL::checkMoveKeys()
{
    bool keys = false;
    std::vector<int> Keys = {32, 30, 17, 31};
    for (int i = 0; i < Keys.size(); i++) {
        if (m_PressedKeys.contains(Keys[i]))
            keys = true;
    }

    if (!keys) {
        m_player->setState(IDLE);
        if (m_player->m_Direct[1] == 1)
            m_player->setState(IDLEUP);
        return;
    }

    std::vector<int> Dirrect = {1, 0};

    if (m_PressedKeys.contains(Keys[0])) {
        Dirrect[0] = 1;
        m_player->setVelocity(5);
        m_player->setState(RUN);
        if (m_PressedKeys.contains(42)) {
            m_player->setVelocity(10);
        }
    } else if (m_PressedKeys.contains(Keys[1])) {
        Dirrect[0] = -1;
        m_player->setVelocity(5);
        m_player->setState(RUN);
        if (m_PressedKeys.contains(42)) {
            m_player->setVelocity(10);
        }
    } else
        Dirrect[0] = 0;
    if (m_PressedKeys.contains(Keys[2])) {
        Dirrect[1] = 1;
        m_player->setVelocity(5);
        m_player->setState(RUN);
        if (m_PressedKeys.contains(42)) {
            m_player->setVelocity(10);
        }
    } else if (m_PressedKeys.contains(Keys[3])) {
        Dirrect[1] = -1;
        m_player->setVelocity(5);
        m_player->setState(RUN);
        if (m_PressedKeys.contains(42)) {
            m_player->setVelocity(10);
        }
    } else
        Dirrect[1] = 0;

    m_player->setDirection(Dirrect[0], Dirrect[1]);
    m_player->move(m_level->tiles);
}

void OpenGL::checkInteractKeys()
{
    bool keys = false;
    std::vector<int> Keys = {28, 57};
    for (int i = 0; i < Keys.size(); i++) {
        if (m_PressedKeys.contains(Keys[i]))
            keys = true;
    }
    if (!keys)
        return;

    if (m_PressedKeys.contains(Keys[0])) {
        std::vector<int> TilePos = {0, 0};
        TilePos[0] = (m_player->m_Pos[0] / TILE_SIZE) + m_player->m_Direct[0];
        TilePos[1] = (m_player->m_Pos[1] / TILE_SIZE) + m_player->m_Direct[1];
        InteractionType type = m_level->tiles[TilePos[1]][TilePos[0]].Interation();
        switch (type) {
        case NOINTERACTION:
            break;
        case CHEST: {
            Chest *chest = (Chest *) m_level->tiles[TilePos[1]][TilePos[0]].getObject();
            emit openChest(*chest);
            break;
        }
        default:
            break;
        }
    }

    if (m_PressedKeys.contains(Keys[1])) {
        m_player->Attack(m_level->tiles);
        m_player->setState(ATTACK);
    }
}
