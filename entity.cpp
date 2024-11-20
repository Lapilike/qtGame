#include "entity.h"
#include <algorithm>
#include <cmath>

using namespace std::chrono;

Entity::Entity()
{
    m_Vel = 0;
    m_State = IDLE;
    Staggered = false;
}

bool Entity::checkCollision(std::vector<std::vector<Tile>> &tiles)
{
    std::vector<std::vector<int>> NextTiles;

    getTilesInFront(NextTiles);

    bool Check = true;

    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].isBlocked()
            || tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() != NOINTERACTION) {
            Check = false;
            break;
        }
    }
    if(Check)
        return false;

    m_Pos[0] += m_Direct[0] * (float)m_Vel;
    m_Pos[1] += m_Direct[1] * (float)m_Vel;

    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].isBlocked()) {
            CollisionBox *Collision = getCollision();
            CollisionBox *Obstacle = tiles[NextTiles[i][1]][NextTiles[i][0]].getCollision();
            Check = Collision->checkIntersect(*Obstacle);

            if(Check) {
                m_Pos[0] -= m_Direct[0] * (float)m_Vel;
                m_Pos[1] -= m_Direct[1] * (float)m_Vel;
                return Check;
            }
        }
        if(!(tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == NOINTERACTION)) {
            CollisionBox *Collision = getCollision();
            Obj *Obstacle = (Obj*)tiles[NextTiles[i][1]][NextTiles[i][0]].getObject();
            CollisionBox *ObstacleCollision = Obstacle->getCollision();
            if(ObstacleCollision == Collision)
                continue;
            Check = Collision->checkIntersect(*Obstacle->getCollision());
            if(Check) {
                m_Pos[0] -= m_Direct[0] * (float)m_Vel;
                m_Pos[1] -= m_Direct[1] * (float)m_Vel;
                return Check;
            }
        }
    }

    m_Pos[0] -= m_Direct[0] * (float)m_Vel;
    m_Pos[1] -= m_Direct[1] * (float)m_Vel;
    return Check;
}
//1
void Entity::getTilesInFront(std::vector<std::vector<int>> &NextTiles)
{
    CollisionBox* collision = getCollision();
    std::vector<float> size = collision->returnSize();
    int xMin = std::min(m_Pos[0], m_Pos[0] + static_cast<int>(m_Direct[0] * m_Vel)) - size[0] / 2;
    int xMax = std::max(m_Pos[0], m_Pos[0] + static_cast<int>(m_Direct[0] * m_Vel)) + size[0] / 2;
    int yMin = std::min(m_Pos[1], m_Pos[1] + static_cast<int>(m_Direct[1] * m_Vel)) - size[1] / 2;
    int yMax = std::max(m_Pos[1], m_Pos[1] + static_cast<int>(m_Direct[1] * m_Vel)) + size[1] / 2;

    int cellXMin = xMin / TILE_SIZE;
    int cellXMax = xMax / TILE_SIZE;
    int cellYMin = yMin / TILE_SIZE;
    int cellYMax = yMax / TILE_SIZE;

    for (int cellX = cellXMin; cellX <= cellXMax; ++cellX) {
        for (int cellY = cellYMin; cellY <= cellYMax; ++cellY) {
            NextTiles.push_back({cellX, cellY});
        }
    }
}

void Entity::normalizeDir()
{
    float abs = m_Direct[0] * m_Direct[0] + m_Direct[1] * m_Direct[1];
    m_Direct[0] = m_Direct[0] / abs;
    m_Direct[1] = m_Direct[1] / abs;
}

void Entity::setVelocity(int vel)
{
    m_Vel = vel;
}

void Entity::setDirection(int xDir, int yDir)
{
    m_Direct[0] = xDir;
    m_Direct[1] = yDir;
}

bool Entity::renderAnim(SpriteRenderer &renderer)
{
    int currFrame = anim[m_State]->currentFrame();
    int TotalFrames = anim[m_State]->totalFrames();
    renderer
        .drawSprite(*anim[m_State]->spriteSheet(), currFrame, TotalFrames, m_Pos, m_Size, m_Direct);
    if (anim[m_State]->increaseCurrFrame())
        return true;

    return false;
}

void Entity::setState(EntityState State)
{
    m_State = State;
}

EntityState Entity::getState()
{
    return m_State;
}

void Entity::stagger()
{
    Staggered = true;
}

void Entity::unStagger()
{
    Staggered = false;
}

bool Entity::isStaggered()
{
    return Staggered;
}

void Entity::move(std::vector<std::vector<Tile>> &tiles)
{
    if (!(checkCollision(tiles)) && !Staggered) {
        int StartX = m_Pos[0] / TILE_SIZE;
        int StartY = m_Pos[1] / TILE_SIZE;
        m_Pos[0] += m_Direct[0] * m_Vel;
        m_Pos[1] += m_Direct[1] * m_Vel;
        if (StartX != m_Pos[0] / TILE_SIZE || StartY != m_Pos[1] / TILE_SIZE) {
            InteractionType Interaction = tiles[StartY][StartX].Interation();
            tiles[StartY][StartX].setObject(nullptr, NOINTERACTION);
            tiles[m_Pos[1] / TILE_SIZE][m_Pos[0] / TILE_SIZE].setObject(this, Interaction);
        }
    }
    m_Vel = 0;


}
