#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include <vector>

class Inventory
{
private:
    int m_ItemAmt;
    std::vector<Item *> m_Items;

public:
    Inventory();
    std::string getItemName(int ItemIndex);
    int getItemAmnt();
    void addItem(Item *);
    Item *removeItem(int);
};

#endif // INVENTORY_H
