#include "entity.h"
#include "opengl.h"

Entity::Entity()
{
    m_Vel = 0;
    m_State = IDLE;
    Staggered = false;
}

bool Entity::checkCollision(std::vector<std::vector<Tile>> tiles)
{
    std::vector<std::vector<int>> NextTiles;

    getTilesInFront(NextTiles);

    if (!tiles[NextTiles[0][1]][NextTiles[0][0]].isBlocked()
        && tiles[NextTiles[0][1]][NextTiles[0][0]].Interation() == NOINTERACTION
        && !tiles[NextTiles[1][1]][NextTiles[1][0]].isBlocked()
        && tiles[NextTiles[1][1]][NextTiles[1][0]].Interation() == NOINTERACTION
        && !tiles[NextTiles[2][1]][NextTiles[2][0]].isBlocked()
        && tiles[NextTiles[2][1]][NextTiles[2][0]].Interation() == NOINTERACTION)
        return false;

    bool Check = false;
  
    m_Pos[0] += m_Direct[0] * (float)m_Vel;
    m_Pos[1] += m_Direct[1] * (float)m_Vel;

    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].isBlocked()) {
            CollisionBox *Collision = getCollision();
            CollisionBox *Obstacle = tiles[NextTiles[i][1]][NextTiles[i][0]].getCollision();
            Check= Collision->checkIntersect(*Obstacle);

            if(Check) {
                m_Pos[0] -= m_Direct[0] * (float)m_Vel;
                m_Pos[1] -= m_Direct[1] * (float)m_Vel;
                return Check;
            }
        }
        if(!(tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == NOINTERACTION)) {
            CollisionBox *Collision = getCollision();
            Obj *Obstacle = (Obj*)tiles[NextTiles[i][1]][NextTiles[i][0]].getObject();
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
    int TilePosX = m_Pos[0] / TILE_SIZE;
    int TilePosY = m_Pos[1] / TILE_SIZE;


    std::vector<float> Direct = {m_Direct[0], m_Direct[1]};
    bool isDiagonal = static_cast<int>(Direct[0] + Direct[1]) % 2 == 0;
    int offsetX, offsetY;
    for(int i = 0; i < 3; i++) {
        if(isDiagonal) {
            offsetX = Direct[0] * ((i + 1) / 2);
            offsetY = Direct[1] * ((i + 1) % 2);
        }
        else {
            int directionModifier = (i % 2 == 0) ? 1 : -1;
            offsetX = Direct[0] + Direct[1] * directionModifier;
            offsetY = Direct[1] + Direct[0] * directionModifier;
        }

        NextTiles.push_back({TilePosX + offsetX, TilePosY + offsetY});
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

void Entity::move(std::vector<std::vector<Tile>> tiles)
{
    if (!(checkCollision(tiles)) && !Staggered) {
        m_Pos[0] += m_Direct[0] * (float) m_Vel;
        m_Pos[1] += m_Direct[1] * (float) m_Vel;
    }
    m_Vel = 0;
}
