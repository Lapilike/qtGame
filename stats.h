#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <map>
#include <vector>

enum StatType {
    HP,
    MSPD,
    ASPD,
    PDMG,
    MDMG,
    PDEF,
    MDEF,
    CRITRATE,
    CRITDMG,
    MAXHP,
};

class Stats
{
private:
    std::map<StatType, short> m_Stats;

public:
    Stats();
    void setStat(std::vector<int>);
    void setStat(int StatType, int StatValue);

    int getStat(int StatType);
    std::map<StatType, short> getStatsMap();
};

#endif // STATS_H
