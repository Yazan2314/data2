//
// Created by yazan on 09/01/2025.
//

#include "UnionFind.h"


UnionFind::UnionFind() : m_teams(), m_teamSize(0) {}

UnionFind::UnionFind(UnionFind &other) = default;

UnionFind::~UnionFind() = default;

std::shared_ptr<team> UnionFind::MakeFleets(int id)
{
    if(m_teams.Contained(id))
        return nullptr;
    try{
        std::shared_ptr<team> newteam = make_shared<team>(id);
        m_teams.addObj(id, newteam);
        m_teamSize++;
       return newteam;
    }
    catch (...)
    {
        throw;
    }


}

void UnionFind::Union(int teamid1, int teamid2){

    std::shared_ptr<team> team1 = m_teams.getObj(teamid1);
    std::shared_ptr<team> team2 = m_teams.getObj(teamid2);
    std::shared_ptr<team> fleet1Root = findRoot(team1);
    std::shared_ptr<team> fleet2Root = findRoot(team2);
    int team1Size = fleet1Root->get_total_jockeys();
    int team2Size = fleet2Root->get_total_jockeys();


    if(team1Size > team2Size) {

    }


    // int fleet1Pirates = fleet1Root->m_numOfPirates;
    // int fleet2Pirates = fleet2Root->m_numOfPirates;
    // if(fleet1Size >= fleet2Size && fleet1Pirates >= fleet2Pirates)
    // {
    //     fleet2Root->m_parent = fleet1Root;
    //     fleet1Root->m_numOfPirates += fleet2Pirates;
    //     fleet1Root->m_numOfShips += fleet2Size;
    //     fleet2->m_isActive = false;
    //     fleet2Root->m_rankExtra += fleet1Pirates;
    //     fleet2Root->m_rankExtra -= fleet1Root->m_rankExtra;
    // }
    // else if( fleet1Size < fleet2Size && fleet1Pirates >= fleet2Pirates)
    // {
    //     fleet1Root->m_parent = fleet2Root;
    //     fleet2Root->m_numOfPirates += fleet1Pirates;
    //     fleet2Root->m_numOfShips += fleet1Size;
    //     fleet2->m_isActive = false;
    //     fleet2Root->m_rankExtra += fleet1Pirates;
    //     fleet1Root->m_rankExtra -= fleet2Root->m_rankExtra;
    // }
    // else if(fleet1Size >= fleet2Size && fleet1Pirates < fleet2Pirates)
    // {
    //     fleet2Root->m_parent = fleet1Root;
    //     fleet1Root->m_numOfPirates += fleet2Pirates;
    //     fleet1Root->m_numOfShips += fleet2Size;
    //     fleet1->m_isActive = false;
    //     fleet1Root->m_rankExtra += fleet2Pirates;
    //     fleet2Root->m_rankExtra -= fleet1Root->m_rankExtra;
    // }
    // else if(fleet1Size < fleet2Size && fleet1Pirates < fleet2Pirates)
    // {
    //     fleet1Root->m_parent = fleet2Root;
    //     fleet2Root->m_numOfPirates += fleet1Pirates;
    //     fleet2Root->m_numOfShips += fleet1Size;
    //     fleet1->m_isActive = false;
    //     fleet1Root->m_rankExtra += fleet2Pirates;
    //     fleet1Root->m_rankExtra -= fleet2Root->m_rankExtra;
    //
    // }

}


std::shared_ptr<fleet> UnionFind::findRoot(std::shared_ptr<fleet> fleet1) {
    if(! fleet1->m_parent.lock())
        return fleet1;
    std::weak_ptr<fleet> parent = fleet1->m_parent;
    return findRoot(parent.lock());
}


std::shared_ptr<fleet> UnionFind::Find(int id) {
    std::shared_ptr<fleet> fleet1 = m_fleets[id];
    if(fleet1 == nullptr)
        return nullptr;
    std::shared_ptr<fleet> root = findRoot(fleet1);
    updateExtra(fleet1);
    pathCompression(fleet1, root);
    return fleet1;
}

void UnionFind::pathCompression(std::shared_ptr<fleet> fleet1, std::shared_ptr<fleet> root)
{
    std::weak_ptr<fleet> parent = fleet1->m_parent;
    if(! parent.lock())
        return;
    fleet1->m_parent = root;
    pathCompression(parent.lock(),root);
}

void UnionFind::updateExtra(std::shared_ptr<fleet> fleet1)
{
    int extra_sum = 0;
    std::shared_ptr<fleet> tmp = fleet1;
    while( tmp )
    {
        if(! tmp->m_parent.lock())
            break;
        extra_sum += tmp->m_rankExtra;
        tmp = tmp->m_parent.lock();
    }
    tmp = fleet1;
    while( tmp )
    {
        int prevRankExtra = tmp->m_rankExtra;
        if(! tmp->m_parent.lock())
            break;
        tmp->m_rankExtra = extra_sum;
        extra_sum -= prevRankExtra;
        tmp = tmp->m_parent.lock();
    }
}

bool UnionFind::Exists(int teamId) {
    if(m_teams.Contained(teamId))
        return true;
    return false;
}

int UnionFind::calcPirateRank(std::shared_ptr<fleet> fleet1) {
    std::weak_ptr<fleet> tmp = fleet1;
    int rank = findRoot(tmp.lock())->m_numOfPirates;
    while( tmp.lock() )
    {
        rank -= tmp.lock()->m_rankExtra;
        tmp = tmp.lock()->m_parent;
    }
    return rank;
}