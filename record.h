//
// Created by yazan on 12/01/2025.
//

#ifndef RECORD_H
#define RECORD_H
#include <memory>

#include "AvlTree.h"
#include "team.h"


class record {
private:
    int id;
    AVLTree<int,std::shared_ptr<team>> teams_tree;


    public:
    record(int id):id(id){}
    ~record()= default;
    int get_id()const { return id; }
    AVLTree<int,std::shared_ptr<team>> &get_teams_tree() {
        return teams_tree;
    }
    void add_team(std::shared_ptr<team> team) {
        teams_tree.addKeyAndData(team->get_team_id(), team);
    }
    void remove_team(std::shared_ptr<team> team) {
        teams_tree.deleteNode(team->get_team_id());
    }



};



#endif //RECORD_H
