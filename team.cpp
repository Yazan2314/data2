//
// Created by yazan on 09/01/2025.
//

#include "team.h"
team::team(int teamid): team_id(teamid) , total_loss(0),total_wins(0) {}

int team::get_balnce_in_team() {
    return total_wins - total_loss;
}
int team::get_team_id() {
    return team_id;
}

int team::get_total_jockeys() const {
    return total_jockeys;
}



