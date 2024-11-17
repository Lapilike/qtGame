#include "item.h"
#include <QDebug>
#include <fstream>

Item::Item()
{
    m_ID = 0;
    m_ItemCount = 1;
    m_Equiped = false;
    m_Stats.setStat(0, 0);
}

Item::Item(int ID)
{
    std::ifstream IDFile(ITEM_ID_FILE);
    if (!IDFile.is_open()) {
        qDebug() << "Error opening Item ID File";
        return;
    }
    std::string line;
    std::stringstream LineStream;
    int tmpId;
    char tmpChar;
    while (std::getline(IDFile, line)) {
        LineStream << line;
        LineStream.get(tmpChar);
        if (tmpChar == '#') {
            LineStream >> tmpId;
            if (tmpId == ID) {
                m_ID = tmpId;
                setStat(LineStream);
                LineStream >> m_Type;
                break;
            }
        }
        LineStream.str(std::string());
        line.clear();
    }
    m_Equiped = false;
    m_ItemCount = 1;

    IDFile.close();
}

void Item::setStat(int StatType, int StatVal)
{
    m_Stats.setStat(StatType, StatVal);
}

void Item::setStat(std::stringstream &LineStream)
{
    std::string buffer;
    int StatAmt;
    LineStream >> m_ItemName;
    LineStream >> StatAmt;
    for (int i = 0; i < StatAmt; i++) {
        std::vector<int> stat = {0, 0};
        LineStream >> stat[0];
        LineStream >> stat[1];
        m_Stats.setStat(stat);
    }
}

void Item::equip()
{
    m_Equiped = true;
}

void Item::unequip()
{
    m_Equiped = false;
}

bool Item::isEquiped()
{
    return m_Equiped;
}

short *Item::amountOfItems()
{
    return &m_ItemCount;
}

int Item::getID()
{
    return m_ID;
}

std::string Item::getName()
{
    return m_ItemName;
}
