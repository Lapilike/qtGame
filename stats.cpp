#include "stats.h"

Stats::Stats() {}

void Stats::setStat(std::vector<int> StatSet)
{
    m_Stats[(StatType) StatSet[0]] = StatSet[1];
}

void Stats::setStat(int Type, int Value)
{
    m_Stats[(StatType) Type] = Value;
}

int Stats::getStat(int Type)
{
    return m_Stats[(StatType) Type];
}

std::map<StatType, short> Stats::getStatsMap()
{
    return m_Stats;
}
