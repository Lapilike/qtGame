#include "inventory.h"

Inventory::Inventory()
{

}

std::string Inventory::getItemName(int ItemIndex)
{
    return m_Items[ItemIndex]->getName();
}

int Inventory::getItemAmnt()
{
    return m_Items.size();;
}

void Inventory::addItem(Item *Itm)
{
    m_Items.push_back(Itm);
}

Item *Inventory::getItem(int ItemID)
{
    for(int i = 0; i < m_Items.size(); i++) {
        if(m_Items[i]->getID() == ItemID)
            return m_Items[i];
    }
}

Item *Inventory::removeItem(int ItemID)
{
    for (int i = 0; i < m_Items.size(); i++) {
        if (m_Items[i]->getID() == ItemID) {
            short *amt = m_Items[i]->amountOfItems();
            if (*amt <= 1) {
                auto iter = m_Items.cbegin();
                Item *tmp = m_Items[i];
                m_Items.erase(iter + i);
                return tmp;
            }
            (*amt)--;
        }
    }

    return nullptr;
}
