#include "enemy.h"
#include <fstream>
#include <sstream>

Enemy::Enemy() {}

Enemy::~Enemy()
{
    delete getCollision();
    delete  texture;
    for (const auto& [State, Anim] : anim)
        delete  Anim;
}

void Enemy::Spawn(std::vector<std::vector<Tile>>& Tiles, int EnemyID, int TilePosX, int TilePosY)
{
    try {
        Tiles.at(TilePosY).at(TilePosX);
    } catch (const std::out_of_range) {
        return;
    }

    Tiles[TilePosY][TilePosX].setObject(this, ENEMY);
    m_Pos[0] = TILE_SIZE * TilePosX + TILE_SIZE / 2;
    m_Pos[1] = TILE_SIZE * TilePosY + TILE_SIZE / 2;

    loadFromFile(EnemyID);
}

void Enemy::loadFromFile(int EnemyID)
{
    std::ifstream IDFile(ENEMY_ID_PATH);
    std::string line;
    std::stringstream lineStream;
    char tmpChar;
    int tmpID;
    int AnimAmnt;
    float width, height;
    while(getline(IDFile, line)) {
        lineStream << line;
        lineStream >> tmpChar;
        lineStream >> tmpID;
        if(tmpChar == '#' && tmpID == EnemyID) {
            lineStream >> width;
            lineStream >> height;
            setNewCollision(width, height);
            lineStream >> AnimAmnt;
            setEnemyAnimation(IDFile, AnimAmnt);
            setStats(IDFile);
            break;
        }
    }
    IDFile.close();
}

void Enemy::getDamaged(int Damage)
{
    int hp = m_Stats.getStat(HP);
    m_Stats.setStat(HP, hp - Damage);
}

bool Enemy::isDead()
{
    bool Dead = m_Stats.getStat(HP) <= 0;
    qDebug() << Dead;
    qDebug() << m_Stats.getStat(HP);
    return  Dead;
}

int Enemy::getStat(int StatType)
{
    return m_Stats.getStat(StatType);
}

void Enemy::setEnemyAnimation(std::ifstream& IDFile, int AnimAmnt)
{
    std::string line;
    std::string AnimationPath;
    std::stringstream lineStream;
    int State, FrameCount, Speed;

    for(int i = 0; i < AnimAmnt; i++) {
        getline(IDFile, line);
        lineStream << line;

        lineStream >> State;
        lineStream >> AnimationPath;
        lineStream >> FrameCount;
        lineStream >> Speed;
        addAnimation(AnimationPath, State, FrameCount, Speed);
        lineStream.clear();
        lineStream.str(std::string());
    }
}

void Enemy::setStats(std::ifstream& IDFile)
{
    std::string line;

    getline(IDFile, line);
    std::stringstream lineStream(line);
    std::vector<int> StatVector = {0, 0};
    while(!lineStream.eof()) {
        lineStream >> StatVector[0];
        lineStream >> StatVector[1];
        m_Stats.setStat(StatVector);
    }
}


