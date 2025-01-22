//
// Created by yazan on 09/01/2025.
//

#include "UnionFind.h"


UnionFind::UnionFind() : m_teams(), m_teamSize(0) {}

UnionFind::UnionFind(UnionFind &other) = default;

UnionFind::~UnionFind() = default;

std::shared_ptr<team> UnionFind::Maketeams(int id)
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

    std::shared_ptr<team> team1 = m_teams[teamid1];
    std::shared_ptr<team> team2 = m_teams[teamid2];

    std::shared_ptr<team> team1Root = Find(teamid1);
    std::shared_ptr<team> team2Root = Find(teamid2);

    int team1jockey = team1Root->get_total_jockeys();
    int team2jockey = team2Root->get_total_jockeys();
    int record_team1 = team1Root->get_record();
    int record_team2 = team2Root->get_record();
    int team1Size = team1Root->get_followers();
    int team2Size = team2Root->get_followers();

    /////fixme: i need to use master- close way


    if (team1Size >= team2Size && record_team1 >= record_team2){ // team1 > team2 and in the union is team1
        team2->change_Active(false);


        team2Root->set_parent(team1Root);


        team1Root->update_record(record_team2);
        team1Root->update_followers(team2Size +1);
        team1Root->update_total_jockeys(team2jockey); /// todo : no need
        if (team1Root->get_leader() != nullptr) {
            team1Root->get_leader()->update_record(record_team2);
            team1Root->get_leader()->update_followers(team2Size + 1);
        }



    }else if (team1Size < team2Size && record_team1 >= record_team2) { /// team1 > team2 and in the union is team2
        // todo the old
        // // team2->change_Active(false);
        // // team1Root->change_parent(team2Root.get());
        //
        // // team1Root->set_parent(team2Root);
        // team2Root->set_parent(team1Root);
        //
        // team1Root->update_record(record_team2);
        // team2Root->update_followers(team1Root->get_followers()+1);
        // team2Root->update_total_jockeys(team1jockey);

        // todo new

        team2->change_Active(false);
        team1Root->set_parent(team2Root);


        if (team1Root->get_leader() != nullptr) {
            team2Root->set_leader(team1Root->get_leader());
            team1Root->get_leader()->update_record(record_team2);
            team1Root->get_leader()->update_followers(team2Size + 1);
            team2Root->update_followers(team1Size + 1);
            team2Root->update_record(record_team1);

            // team1Root->get_record_parent()->update_followers(team2Root->get_followers() +1);
            // team1Root->get_record_parent()->update_record(team2Root->get_record());
            // team2Root->update_followers(temp + 1);
            // team2Root->update_record(temp2);


        }else {
            team2Root->set_leader(team1Root);
            team1Root->update_record(record_team2);
            team1Root->update_followers(team2Size + 1);
            team2Root->update_followers(team1Size + 1);
            team2Root->update_record(record_team1);

            // team1Root->update_followers(team2Root->get_followers() +1);
            // team1Root->update_record(team2Root->get_record() );
            // team2Root->update_followers(temp + 1);
            // team2Root->update_record(temp2);
        }

    }else if (team1Size >= team2Size && record_team1 < record_team2) {/// team1 < team2 and in the union is team1

        ///todo old
        // team1->change_Active(false);
        // // team2Root->change_parent(team1Root.get());
        // // team2Root->set_parent(team1Root);
        // team1Root->set_parent(team2Root);
        //
        // team2Root->update_record(record_team1);
        // team1Root->update_followers(team2Root->get_followers()+1);
        // team1Root->update_total_jockeys(team2jockey);
        //

        // todo new;
        team1->change_Active(false);
        team2Root->set_parent(team1Root);

        if (team2Root->get_leader() != nullptr) {
            team1Root->set_leader(team2Root->get_leader());

            team2Root->get_leader()->update_record(record_team1);
            team2Root->get_leader()->update_followers(team1Size + 1);
            team1Root->update_followers(team2Size + 1);
            team1Root->update_record(record_team2);
        }else {
            team1Root->set_leader(team2Root);
            team2Root->update_record(record_team1);
            team2Root->update_followers(team1Size + 1);
            team1Root->update_followers(team2Size + 1);
            team1Root->update_record(record_team2);
        }


    }else if (team1Size < team2Size && record_team1 < record_team2) {   /// team1 < team2 and in the union is team2
        team1->change_Active(false);
        // team1Root->change_parent(team2Root.get());

        team1Root->set_parent(team2Root);

        team2Root->update_record(record_team1);
        team2Root->update_followers(team1Root->get_followers()+1);
        team2Root->update_total_jockeys(team1jockey);

        if (team2Root->get_leader() != nullptr) {
            team2Root->get_leader()->update_record(record_team1);
            team2Root->get_leader()->update_followers(team1Size + 1);
        }

    }

}


std::shared_ptr<team> UnionFind::findRoot(std::shared_ptr<team> team1) {
    if( team1->get_parent_ptr() == nullptr) {
        return team1;
    }

    auto  parent = team1->get_parent_ptr();
    return findRoot(parent);
}


std::shared_ptr<team> UnionFind::Find(int id) {
    std::shared_ptr<team> team1 = m_teams[id];
    if(team1 == nullptr)
        return nullptr;
    std::shared_ptr<team> root = findRoot(team1);

    // updateExtra(fleet1); /// todo : i dont know what for mabey we dont need it
    pathCompression(team1, root);
    return root;
}

void UnionFind::pathCompression(std::shared_ptr<team> team1, std::shared_ptr<team> root){
    auto parent = team1->get_parent_ptr();
    if(parent == nullptr)
        return;
    team1->change_parent(root.get());
    pathCompression(parent,root);
}

// void UnionFind::updateExtra(std::shared_ptr<fleet> fleet1){ /// todo : i dont know this function what for
//     int extra_sum = 0;
//     std::shared_ptr<fleet> tmp = fleet1;
//     while( tmp )
//     {
//         if(! tmp->m_parent.lock())
//             break;
//         extra_sum += tmp->m_rankExtra;
//         tmp = tmp->m_parent.lock();
//     }
//     tmp = fleet1;
//     while( tmp )
//     {
//         int prevRankExtra = tmp->m_rankExtra;
//         if(! tmp->m_parent.lock())
//             break;
//         tmp->m_rankExtra = extra_sum;
//         extra_sum -= prevRankExtra;
//         tmp = tmp->m_parent.lock();
//     }
// }

bool UnionFind::Exists(int teamId) {
    if(m_teams.Contained(teamId))
        return true;
    return false;
}

// int UnionFind::calcPirateRank(std::shared_ptr<fleet> fleet1) {
//     std::weak_ptr<fleet> tmp = fleet1;
//     int rank = findRoot(tmp.lock())->m_numOfPirates;
//     while( tmp.lock() )
//     {
//         rank -= tmp.lock()->m_rankExtra;
//         tmp = tmp.lock()->m_parent;
//     }
//     return rank;
// } todo :  i don't know this function what for