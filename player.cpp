#include "player.h"
#include "stats.h"
#include "enemy.h"

Player::Player() {
    setNewCollision(13.125f, 28.125f);
    setStats();

    m_Attack = new Obj;
    m_Attack->setSize(1, 2);

};

void Player::Attack(std::vector<std::vector<Tile>> tiles)
{
    m_Attack->addAnimation(":/Animations/Attack/Attack", IDLE, 8, 2);
    m_Attack->setPosition(m_Pos[0] + m_Direct[0] * (TILE_SIZE - 10), m_Pos[1] + m_Direct[1] * (TILE_SIZE - 10));
    m_Attack->setDirection(m_Direct[0], m_Direct[1]);

    std::vector<float> position = {0, 0};
    Obj* CheckSquare = new Obj;
    position[0] = m_Pos[0] + m_Direct[0] * TILE_SIZE;
    position[1] = m_Pos[1] + m_Direct[1] * TILE_SIZE;
    CheckSquare->setPosition(position[0], position[1]);
    CheckSquare->setNewCollision(abs(15 + 45 * m_Direct[1]), abs(15 + 45 * m_Direct[0]));
    std::vector<std::vector<int>> NextTiles;
    getTilesInFront(NextTiles);
    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == ENEMY) {
            CollisionBox *Collision = CheckSquare->getCollision();
            Enemy* enemy = (Enemy*)tiles[NextTiles[i][1]][NextTiles[i][0]].getObject();
            if(Collision->checkIntersect(*enemy->getCollision())) {
                int Damage = m_Stats.getStat(PDMG) + m_Stats.getStat(MDMG);
                enemy->getDamaged(Damage);
            }

        }
    }
    stagger();
    setState(ATTACK);
    delete CheckSquare;
}

void Player::drawAttack(SpriteRenderer &renderer)
{
    int angle = atan(m_Attack->m_Direct[1]/m_Attack->m_Direct[0]) * 180 / M_PI;
    m_Attack->renderAnim(renderer, angle);
}

void Player::setStats()
{
    m_Stats.setStat(PDMG, 10);
    m_Stats.setStat(MDMG, 0);
}

void Player::getDamaged(int Damage)
{
    int hp = m_Stats.getStat(HP);
    m_Stats.setStat(HP, hp - Damage);
}
