//
// Created by yazan on 09/01/2025.
//

#ifndef TEAM_H
#define TEAM_H
#include <memory>

class team {
  int team_id;
  int record ;
  bool isActive;
  int total_jockeys;
  team* parent;
  std::shared_ptr<team> parent_ptr;
  int followers; /// the number of teams foolow him in the unionfind opiste tree

  public:

  team(int teamid);
  ~team() = default;
  int get_team_id();
  int get_total_jockeys() const;
  void change_Active(bool actvie);
  bool is_Active() const;
  void change_parent(team* new_parent);
  team* get_parent() const;
  void update_record(int num);
  int get_record() const;

  void update_total_jockeys(int num);
  void update_followers(int num);
  int get_followers() const;

  std::shared_ptr<team> get_parent_ptr() const;
  void set_parent(std::shared_ptr<team> new_parent);

};




#endif //TEAM_H
