#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include <vector>

class Inventory
{
private:
    std::vector<Item *> m_Items;

public:
    Inventory();
    std::string getItemName(int ItemIndex);
    int getItemAmnt();
    void addItem(Item *);
    Item* getItem(int ItemID);
    Item *removeItem(int ItemID);
};

#endif // INVENTORY_H
