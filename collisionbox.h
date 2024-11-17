#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include <vector>

class CollisionBox
{
    std::vector<int> *m_Pos;
    std::vector<float> m_Size;
public:
    CollisionBox();
    ~CollisionBox() {};
    CollisionBox(std::vector<int> *vector);
    void setPositionVector(std::vector<int> *vector);
    void setSize(float width, float height);
    std::vector<float> returnSize();
    bool checkIntersect(CollisionBox obstacle);
};

#endif // COLLISIONBOX_H
