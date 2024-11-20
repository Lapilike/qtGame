#include "bleb.h"
#include "qtimer.h"
#include <QtConcurrent/QtConcurrent>

Bleb::Bleb(std::vector<std::vector<Tile>> *tiles, int TilePosX, int TilePosY, Player* player) {
    uintptr_t UID = reinterpret_cast<uintptr_t>(this);
    setUID(UID);
    Spawn(*tiles, 0, TilePosX, TilePosY);
    TriggerDistance = 4;
    m_AttackRange = 1;
    m_Attack = new Obj;
    m_Attack->addAnimation(":/Animations/Enemies/Bleb/Attack", IDLE, 9, 6);    m_Attack->setSize(3, 3);
    m_Attack->setDirection(0, 1);
    timer = new QTimer();
    Bleb::connect(timer, &QTimer::timeout, [=]() {
        QtConcurrent::run([tiles, player, this]() {
            int DistancePlayer = sqrt(pow(m_Pos[0] -  player->m_Pos[0], 2) + pow(m_Pos[1] -  player->m_Pos[1], 2));
            if(!isStaggered()) {
                if(DistancePlayer < m_AttackRange * TILE_SIZE && m_Attack->anim[IDLE]->currentFrame() == 0)
                    Attack(*tiles, player);
                else
                    moveInPattern(tiles, player->m_Pos);
            }
        });
    });
        timer->start(29);
}

void Bleb::moveInPattern(std::vector<std::vector<Tile>> *tiles, std::vector<int> &PlayerPos)
{
    int curFrame = anim[RUN]->currentFrame();
    int TotalFrames = anim[RUN]->totalFrames();
    if (isTriggered(PlayerPos) || ((curFrame < TotalFrames) && curFrame != 0)) {
        setState(RUN);
        if(anim[RUN]->currentFrame() <= 2 || anim[RUN]->currentFrame() >= 6)
            return;
        setVelocity(5);
        std::vector<int> Direct = {
            PlayerPos[0] - m_Pos[0],
            PlayerPos[1] - m_Pos[1] + 1
        };
        if(PlayerPos[0] - m_Pos[0] != 0) {
            m_Direct[0] = Direct[0] / abs(Direct[0]);
            m_Direct[1] = 0;
        }
        else if(PlayerPos[1] - m_Pos[1] != 0) {
            m_Direct[0] = 0;
            m_Direct[1] = Direct[1] / abs(Direct[1]);
        }
        else {
            setState(IDLE);
            setVelocity(0);
            return;
        }
        move(*tiles);
        return;
    }
    setState(IDLE);
    setVelocity(0);
}

void Bleb::Attack(std::vector<std::vector<Tile>> &tiles, Player* player)
{
    m_Attack->setPosition(m_Pos[0], m_Pos[1]);
    std::vector<float> position = {0, 0};
    Obj* CheckSquare = new Obj;
    CheckSquare->setPosition(m_Pos[0], m_Pos[1]);
    CheckSquare->setNewCollision(90, 90);
    CollisionBox *Collision = CheckSquare->getCollision();
    if(Collision->checkIntersect(*player->getCollision())) {
        int Damage = CalcDamage(player->getStats());
        player->getDamaged(Damage);
        qDebug() << player->getStat(HP);
    }
    stagger();
    setState(ATTACK);
    delete CheckSquare;
}

bool Bleb::drawAttack(SpriteRenderer &renderer)
{
    return m_Attack->renderAnim(renderer);
}

bool Bleb::isTriggered(std::vector<int> PlayerPos)
{
    int DistancePlayer = sqrt(pow(m_Pos[0] - PlayerPos[0], 2) + pow(m_Pos[1] - PlayerPos[1], 2));
    int Trigger = TriggerDistance * TILE_SIZE;
    return  Trigger >= DistancePlayer;
}
