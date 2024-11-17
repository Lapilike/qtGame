#ifndef ITEM_H
#define ITEM_H
#include "stats.h"
#include <sstream>
#include <vector>

#define ITEM_ID_FILE "Data/IDs/ItemID.txt"

enum ItemType {
    HELMET,
    CHESTPLATE,
    LEGINGS,
    BOOTS,
    ONE_HAND,
    TWO_HANDS,
};

class Item
{
private:
    short m_ID;
    short m_ItemCount;
    short m_Type;
    bool m_Equiped;
    std::string m_ItemName;
    Stats m_Stats;

public:
    Item();
    Item(int ID);
    void setStat(int StatType, int StatValue);
    void setStat(std::stringstream &LineStream);
    void equip();
    void unequip();
    bool isEquiped();
    short *amountOfItems();
    int getID();
    std::string getName();
};

#endif // ITEM_H
