#include "collisionbox.h"
#include "obj.h"

CollisionBox::CollisionBox()
{
    m_Pos = nullptr;
    m_Size = {TILE_SIZE, TILE_SIZE};
}

CollisionBox::CollisionBox(std::vector<int> *vector)
{
    m_Pos = vector;
    m_Size = {TILE_SIZE, TILE_SIZE};
}

void CollisionBox::setPositionVector(std::vector<int> *vector)
{
    m_Pos = vector;
}

void CollisionBox::setSize(float width, float height)
{
    m_Size[0] = width;
    m_Size[1] = height;
}

std::vector<float> CollisionBox::returnSize()
{
    return m_Size;
}

bool CollisionBox::checkIntersect(CollisionBox obstacle)
{
    std::vector<bool> CollisionVector = {false, false};

    std::vector<float> ObstacleBorder = {0, 0, 0, 0};
    std::vector<float> CollisionBorder = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        CollisionBorder[i] = (*m_Pos)[i / 2] + pow(-1, i) * m_Size[i / 2];
        ObstacleBorder[i] = (*obstacle.m_Pos)[i / 2] + pow(-1, i) * obstacle.m_Size[i / 2];
    }

    CollisionVector[0] = (ObstacleBorder[0] >= CollisionBorder[1])
                         && (ObstacleBorder[1] <= CollisionBorder[0]);
    CollisionVector[1] = (ObstacleBorder[2] >= CollisionBorder[3])
                         && (ObstacleBorder[3] <= CollisionBorder[2]);

    return CollisionVector[0] && CollisionVector[1];
}
