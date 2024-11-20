#include "player.h"
#include "stats.h"

Player::Player()
    : QObject(), Entity()
{
    setNewCollision(13.125f, 28.125f);
    setStats();

    m_Attack = new Obj;
    m_Attack->setSize(1, 2);

    //loadAnimations();

    addItem(0, 1);
    eqiupItem(0);
    addItem(34, 1);
    eqiupItem(34);
}

void Player::loadAnimations()
{
    anim[IDLE] = new Animation;
    anim[IDLE]->addAnimation(":/Animations/Player/Player_Idle", 6, 8);
    anim[IDLEUP] = new Animation;
    anim[IDLEUP]->addAnimation(QImage(":/Animations/Player/Player_Idle_Up"), 6, 8);
    anim[RUN] = new Animation;
    anim[RUN]->addAnimation(QImage(":/Animations/Player/Player_Run"), 4, 3);
    anim[ATTACK] = new Animation;
    anim[ATTACK]->addAnimation(QImage(":/Animations/Player/Player_Attack"), 8, 2);
};

void Player::Attack(std::vector<std::vector<Tile>> tiles)
{
    m_Attack->addAnimation(":/Animations/Attack/Attack", IDLE, 8, 2);
    m_Attack->setPosition(m_Pos[0] + m_Direct[0] * (TILE_SIZE - 10),
                          m_Pos[1] + m_Direct[1] * (TILE_SIZE - 10));
    m_Attack->setDirection(m_Direct[0], m_Direct[1]);

    std::vector<float> position = {0, 0};
    Obj *CheckSquare = new Obj;
    position[0] = m_Pos[0] + m_Direct[0] * TILE_SIZE;
    position[1] = m_Pos[1] + m_Direct[1] * TILE_SIZE;
    CheckSquare->setPosition(position[0], position[1]);
    CheckSquare->setNewCollision(abs(15 + 45 * m_Direct[1]), abs(15 + 45 * m_Direct[0]));
    std::vector<std::vector<int>> NextTiles;
    getTiles(NextTiles);
    for (int i = 0; i < NextTiles.size(); i++) {
        if (tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == ENEMY) {
            CollisionBox *Collision = CheckSquare->getCollision();
            Enemy *enemy = (Enemy *) tiles[NextTiles[i][1]][NextTiles[i][0]].getObject();
            if (Collision->checkIntersect(*enemy->getCollision())) {
                int Damage = CalcDamage(enemy);
                if(enemy->getDamaged(Damage)) {
                    emit EnemyDied(enemy);
                }
            }
        }
    }
    stagger();
    setState(ATTACK);
    delete CheckSquare;
}

int Player::CalcDamage(Enemy* enemy)
{
    int HP = enemy->getStat(MAXHP);
    int Mdef = enemy->getStat(MDEF);
    int Pdef = enemy->getStat(MDEF);
    float MDMGReduction = static_cast<float>(-HP * (HP / (2 * Mdef + HP) + 1)) / 100.0;
    float PDMGReduction = static_cast<float>(-HP * (HP / (2 * Pdef + HP) + 1)) / 100.0;
    int Damage = (m_Stats.getStat(PDMG) - (int)(PDMGReduction * m_Stats.getStat(PDMG))) + (m_Stats.getStat(MDMG) - (int)(MDMGReduction * m_Stats.getStat(MDMG)));
    return Damage;
}

void Player::drawAttack(SpriteRenderer &renderer)
{
    int angle = atan(m_Attack->m_Direct[1] / m_Attack->m_Direct[0]) * 180 / M_PI;
    m_Attack->renderAnim(renderer, angle);
}

void Player::setStats()
{
    m_Stats.setStat(HP, 100);
    m_Stats.setStat(MAXHP, 100);
    m_Stats.setStat(MDEF, 0);
    m_Stats.setStat(PDEF, 0);
    m_Stats.setStat(PDMG, 10);
    m_Stats.setStat(MDMG, 0);
}

int Player::getStat(int StatType)
{
    return m_Stats.getStat(StatType);
}

void Player::getDamaged(int Damage)
{
    int hp = m_Stats.getStat(HP);
    m_Stats.setStat(HP, hp - Damage);
}

void Player::getTiles(std::vector<std::vector<int>> &NextTiles)
{
    NextTiles.resize(3);
    int TilePosX = m_Pos[0] / TILE_SIZE;
    int TilePosY = m_Pos[1] / TILE_SIZE;
    NextTiles[0] = {static_cast<int>(TilePosX + m_Direct[0]), static_cast<int>(TilePosY + m_Direct[1])};
    NextTiles[1] = {static_cast<int>(TilePosX + m_Direct[1]), static_cast<int>(TilePosY - m_Direct[0])};
    NextTiles[2] = {static_cast<int>(TilePosX - m_Direct[1]), static_cast<int>(TilePosY + m_Direct[0])};
}

void Player::addItem(int ItemID, int ItemAmnt) {
    Item* item = new Item(ItemID);
    item->setAmnt(ItemAmnt);
    m_Inv.addItem(item);
}

void Player::eqiupItem(int ItemID)
{
    Item* item = m_Inv.getItem(ItemID);
    item->equip();
    std::map<StatType, short> Stats = item->getStats();
    for (const auto& [Type, Value] : Stats)
        m_Stats.setStat(Type, m_Stats.getStat(Type) + Value);

}

Stats *Player::getStats()
{
    return &m_Stats;
}
