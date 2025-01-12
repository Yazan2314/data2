//
// Created by yazan on 09/01/2025.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "team.h"
#include "hashTable.h"
#include <memory>

class UnionFind
{
public:
    HashTable<std::shared_ptr<team>> m_teams;
    int m_teamSize;

    UnionFind();
    UnionFind(UnionFind& other);
    ~UnionFind();
    std::shared_ptr<team> Maketeams(int id);
    void Union(int teamId1, int teamId2);
    std::shared_ptr<team> findRoot(std::shared_ptr<team> team1);
    std::shared_ptr<team> Find(int id);
    void pathCompression(std::shared_ptr<team> fleet1, std::shared_ptr<team> root);
    void updateExtra(std::shared_ptr<team> team1);
    bool Exists(int teamId);
    int calcPirateRank(std::shared_ptr<team> team1);

};






#endif //UNIONFIND_H
