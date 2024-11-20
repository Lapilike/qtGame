#include "enemymanager.h"
#include "bleb.h"
#include "qtimer.h"

#include <ctime>
#include <cstdint>

EnemyManager::EnemyManager(SpriteRenderer *Renderer)
{
    m_Wave = 0;
    m_Renderer = Renderer;
}

void EnemyManager::spawnEnemies(std::vector<std::vector<Tile> > &tiles, Player* player)
{
    m_Wave++;
    std::vector<void*> Blebs = spawnBleb(tiles, player);
    m_Enemies[BLEB] = Blebs;
}

std::vector<void*> EnemyManager::spawnBleb(std::vector<std::vector<Tile> > &tiles, Player* player)
{
    std::vector<void*> Blebs;
    CalcEnemyCount();
    srand(time(0));
    int TilePosX, TilePosY;
    for(int i = 0; i < m_EnemyAmnt % 10; i++) {
        do {
            TilePosX = rand() % 30;
            TilePosY = rand() % 16;
        } while(TilePosX == player->m_Pos[0] / TILE_SIZE || TilePosY == player->m_Pos[1] / TILE_SIZE);
        Bleb* Enemy = new Bleb(&tiles, TilePosX, TilePosY, player);
        Blebs.push_back(Enemy);
    };

    return Blebs;
}

void EnemyManager::CalcEnemyCount()
{
    int Cur = 1;
    int Prev = Cur;
    for(int i = 1; i < m_Wave; i++)
        Cur += Prev;

    m_EnemyAmnt = Cur;
}

void EnemyManager::drawEnemies()
{
    for(const auto& [Type, Enemies] : m_Enemies) {
        for(int i = 0; i < Enemies.size(); i++) {
            switch (Type) {
            case BLEB: {
                Bleb* Enemy = (Bleb*)Enemies[i];
                Enemy->renderAnim(*m_Renderer);
                if(Enemy->getState() == ATTACK) {
                    if(Enemy->drawAttack(*m_Renderer)) {
                        Enemy->setState(IDLE);
                        QTimer::singleShot(1000, [=]() {Enemy->unStagger();});
                    }
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

bool EnemyManager::isAllDead()
{
    return m_EnemyAmnt == 0;
}

void EnemyManager::enemyDeath(Enemy *enemy)
{
    for (auto it = m_Enemies.begin(); it != m_Enemies.end(); ++it) {
        std::vector<void*>& Enemies = it->second;
        uintptr_t UID;
        for(int i = 0; i < Enemies.size(); i++) {
            UID = reinterpret_cast<uintptr_t>(Enemies[i]);
            if(UID == enemy->getUID()) {
                Enemies.erase(Enemies.cbegin() + i);
                emit enemyDied(enemy);
            }
        }
    }
    m_EnemyAmnt--;
}


