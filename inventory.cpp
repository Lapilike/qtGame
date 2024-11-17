#include "inventory.h"

Inventory::Inventory() {
    m_ItemAmt = 0;
}

std::string Inventory::getItemName(int ItemIndex)
{
    return m_Items[ItemIndex]->getName();
}

int Inventory::getItemAmnt()
{
    return m_ItemAmt;
}

void Inventory::addItem(Item* Itm) {
    m_ItemAmt++;
    m_Items.push_back(Itm);
}

Item* Inventory::removeItem(int ItmID) {
    for(int i = 0; i < m_Items.size(); i++) {
        if(m_Items[i]->getID() == ItmID) {
            short* amt = m_Items[i]->amountOfItems();
            if(*amt <= 1) {
                auto iter = m_Items.cbegin();
                Item* tmp = m_Items[i];
                m_Items.erase(iter + i);
                return tmp;
            }
            (*amt)--;
        }
    }

    return nullptr;
}
