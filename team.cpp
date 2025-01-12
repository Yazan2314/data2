//
// Created by yazan on 09/01/2025.
//

#include "team.h"
team::team(int teamid): team_id(teamid) , record(0),isActive(true),parent(nullptr),parent_ptr(nullptr) {}


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



std::shared_ptr<team> team::get_parent_ptr() const {
    return parent_ptr;
}
void team::set_parent(std::shared_ptr<team> new_parent) {
    parent_ptr = new_parent;
}











