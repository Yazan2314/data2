//
// Created by yazan on 09/01/2025.
//

#include "team.h"
// team::team(int teamid): team_id(teamid) , record(0),   followers(0),  total_jockeys(0)  ,isActive(true),parent(nullptr),parent_ptr(nullptr){}
team::team(int teamid)
    : team_id(teamid), record(0), isActive(true), total_jockeys(0),
      parent(nullptr), parent_ptr(nullptr), followers(0) ,record_parent(nullptr){}

int team::get_team_id() {
    return team_id;
}

int team::get_total_jockeys() const {
    return total_jockeys;
}


void team::change_Active(bool active) {
    isActive = active;
}
void team::change_parent(team *new_parent) {
    parent = new_parent;
}

void team::update_record(int num) {
    record += num;
}

int team::get_record() const {
    return record;
}

void team::update_total_jockeys(int num) {
    total_jockeys += num;
}


int team::get_followers() const {
    return followers;
}

void team::update_followers(int num) {
    followers += num;
}

bool team::is_Active() const {
    return isActive;
}
team *team::get_parent() const {
    return parent;
}


team *team::get_record_parent() const {
    return record_parent;
}

void team::update_record_parent(team *new_parent) {
    record_parent = new_parent;
}




std::shared_ptr<team> team::get_parent_ptr() const {
    return parent_ptr;
}
void team::set_parent(std::shared_ptr<team> new_parent) {
    parent_ptr = new_parent;
}





std::shared_ptr<team> team::get_leader() const {
    return leader.lock();
}
void team::set_leader(std::shared_ptr<team> new_leader) {
    leader = new_leader;
}













