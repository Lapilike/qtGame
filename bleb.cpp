#include "bleb.h"
#include "qtimer.h"
#include <QtConcurrent/QtConcurrent>

Bleb::Bleb(std::vector<std::vector<Tile>> *tiles, int TilePosX, int TilePosY, std::vector<int> *PlayerPos) {
    Spawn(*tiles, 0, TilePosX, TilePosY);
    TriggerDistance = 4;
    timer = new QTimer();
    Bleb::connect(timer, &QTimer::timeout, [=]() {
        QtConcurrent::run([=]() { moveInPattern(tiles, PlayerPos); });
    });
    timer->start(1000/60.0f);
}

void Bleb::moveInPattern(std::vector<std::vector<Tile>> *tiles, std::vector<int> *PlayerPos)
{
    if(isTriggered((*PlayerPos))) {
        setState(RUN);
        setVelocity(5);
        std::vector<int> Direct = {
            (*PlayerPos)[0] - m_Pos[0],
            (*PlayerPos)[1] - m_Pos[1] + 1
        };
        if((*PlayerPos)[0] - m_Pos[0] != 0) {
            m_Direct[0] = Direct[0] / abs(Direct[0]);
            m_Direct[1] = 0;
        }
        else if((*PlayerPos)[1] - m_Pos[1] != 0) {
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

void Bleb::Attack(std::vector<std::vector<Tile>> tiles, Player* player)
{
    m_Attack->addAnimation(":/Animations/Enemies/Bleb/Attack", IDLE, 4, 4);
    m_Attack->setPosition(m_Pos[0], m_Pos[1]);
    m_Attack->setSize(2, 2);
    m_Attack->setDirection(0, 1);

    std::vector<float> position = {0, 0};
    Obj* CheckSquare = new Obj;
    CheckSquare->setPosition(m_Pos[0], m_Pos[1]);
    CheckSquare->setNewCollision(60, 60);
    std::vector<std::vector<int>> NextTiles;

    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == ENEMY) {
            CollisionBox *Collision = CheckSquare->getCollision();
            if(Collision->checkIntersect(*player->getCollision())) {
                int Damage = getStat(PDMG) + getStat(MDMG);
                player->getDamaged(Damage);
            }

        }
    }
    stagger();
    setState(IDLE);
    delete CheckSquare;
}

bool Bleb::isTriggered(std::vector<int> PlayerPos)
{
    int DistancePlayer = sqrt(pow(m_Pos[0] - PlayerPos[0], 2) + pow(m_Pos[1] - PlayerPos[1], 2));
    int Trigger = TriggerDistance * TILE_SIZE;
    return  Trigger >= DistancePlayer;
}
