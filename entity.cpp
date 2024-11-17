#include "entity.h"
#include "opengl.h"

Entity::Entity() {
    m_Vel = 0;
    m_State = IDLE;
    Staggered = false;
}

std::vector<bool> Entity::checkIntersect(std::vector<float> tile)
{
    std::vector<bool> CollisionVector = {false, false};

    CollisionVector[0] = (tile[0] > (m_Pos[0] - TILE_SIZE/2)) && (tile[1] < (m_Pos[0] + TILE_SIZE/2));
    CollisionVector[1] = (tile[2] > (m_Pos[1] - TILE_SIZE/2)) && (tile[3] < (m_Pos[1] + TILE_SIZE/2));

    return CollisionVector;
}

bool Entity::checkCollision(std::vector<std::vector<Tile>> tiles)
{
    std::vector<std::vector<int>> NextTiles;

    getTilesInFront(NextTiles);

    if(!tiles[NextTiles[0][1]][NextTiles[0][0]].isBlocked() && tiles[NextTiles[0][1]][NextTiles[0][0]].Interation() == NOINTERACTION
    && !tiles[NextTiles[1][1]][NextTiles[1][0]].isBlocked() && tiles[NextTiles[1][1]][NextTiles[1][0]].Interation() == NOINTERACTION
    && !tiles[NextTiles[2][1]][NextTiles[2][0]].isBlocked() && tiles[NextTiles[2][1]][NextTiles[2][0]].Interation() == NOINTERACTION)
        return false;

    bool Check = false;
    for(int i = 0; i < NextTiles.size(); i++) {
        if(tiles[NextTiles[i][1]][NextTiles[i][0]].isBlocked()) {
            m_Pos[0] += m_Direct[0] * (float)m_Vel;
            m_Pos[1] += m_Direct[1] * (float)m_Vel;

            CollisionBox *Collision = getCollision();
            CollisionBox *Obstacle = tiles[NextTiles[i][1]][NextTiles[i][0]].getCollision();
            Check= Collision->checkIntersect(*Obstacle);
            m_Pos[0] -= m_Direct[0] * (float)m_Vel;
            m_Pos[1] -= m_Direct[1] * (float)m_Vel;
            if(Check) return Check;
        }
        if(!(tiles[NextTiles[i][1]][NextTiles[i][0]].Interation() == NOINTERACTION)) {
            m_Pos[0] += m_Direct[0] * (float)m_Vel;
            m_Pos[1] += m_Direct[1] * (float)m_Vel;

            CollisionBox *Collision = getCollision();
            Obj *Obstacle = (Obj*)tiles[NextTiles[i][1]][NextTiles[i][0]].getObject();

            m_Pos[0] -= m_Direct[0] * (float)m_Vel;
            m_Pos[1] -= m_Direct[1] * (float)m_Vel;
            Check = Collision->checkIntersect(*Obstacle->getCollision());
            if(Check) return Check;
        }
    }

    return Check;
}

void Entity::getTilesInFront(std::vector<std::vector<int>> &NextTiles)
{
    int TilePosX = m_Pos[0] / TILE_SIZE;
    int TilePosY = m_Pos[1] / TILE_SIZE;

    std::vector<int> Direct = {(int)ceil(m_Direct[0]), (int)ceil(m_Direct[1])};
    if(!((int)(Direct[0] + Direct[1]) % 2)) {
        for(int i = 0; i < 3; i++) {
            std::vector<int> Tile = {0, 0};
            Tile[0] = TilePosX + Direct[0] * ((i + 1) / 2);
            Tile[1] = TilePosY + Direct[1] * ((i + 1) % 2);
            NextTiles.push_back(Tile);
        }
    }
    else {
        for(int i = 0; i < 3; i++) {
            std::vector<int> Tile = {0, 0};
            Tile[0] = TilePosX + Direct[0] + ((i + 1) / 2) * Direct[1] * pow(-1, i);
            Tile[1] = TilePosY + Direct[1] + ((i + 1) / 2) * Direct[0] * pow(-1, i);
            NextTiles.push_back(Tile);
        }
    }
}

void Entity::normalizeDir() {
    float abs = m_Direct[0] * m_Direct[0] + m_Direct[1] * m_Direct[1];
    m_Direct[0] = m_Direct[0]/abs;
    m_Direct[1] = m_Direct[1]/abs;
}

void Entity::setVelocity(int vel) {
    m_Vel = vel;
}

void Entity::setDirection(int xDir, int yDir) {
    m_Direct[0] = xDir;
    m_Direct[1] = yDir;
}



bool Entity::renderAnim(SpriteRenderer &renderer)
{
    int currFrame = anim[m_State]->currentFrame();
    int TotalFrames = anim[m_State]->totalFrames();
    renderer.drawSprite(*anim[m_State]->spriteSheet(), currFrame, TotalFrames, m_Pos, m_Size, m_Direct);
    if(anim[m_State]->increaseCurrFrame())
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

void Entity::move(std::vector<std::vector<Tile>> tiles) {
    if(!(checkCollision(tiles)) && !Staggered)
    {
        m_Pos[0] += m_Direct[0] * (float)m_Vel;
        m_Pos[1] += m_Direct[1] * (float)m_Vel;
    }
    m_Vel = 0;
}
