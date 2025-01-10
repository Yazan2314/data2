//
// Created by yazan on 09/01/2025.
//

#ifndef TEAM_H
#define TEAM_H

class team {
  int team_id;
  int total_wins;
  int total_loss;
  bool isActive;
  int total_jockeys;

  public:
  team(int teamid);
  ~team() = default;
  int get_team_id();
  int get_balnce_in_team();
  int get_total_jockeys() const;
};



#endif //TEAM_H
