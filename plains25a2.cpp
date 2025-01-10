// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains()
{
    Teams = new UnionFind();
    
}

Plains::~Plains()
{
    delete Teams;
}

StatusType Plains::add_team(int teamId){
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (Teams->Exists(teamId)) {
        return StatusType::FAILURE;
    }
    try {
        Teams->MakeFleets(teamId);

    }catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
      return StatusType::SUCCESS;

}

StatusType Plains::add_jockey(int jockeyId, int teamId){
if (teamId <= 0 || jockeyId <= 0) {
    return StatusType::INVALID_INPUT;
}
    if (!Teams->Exists(teamId) || jockey_table.Contained(jockeyId)) {
        return StatusType::FAILURE;
    }
    try {
        std::shared_ptr<jockey> new_jockey = std::make_shared<jockey>(jockeyId,teamId);
        jockey_table.addObj(jockeyId,new_jockey);

    }catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId){
    if (losingJockeyId <= 0 || victoriousJockeyId <= 0 || losingJockeyId == victoriousJockeyId) {
        return StatusType::INVALID_INPUT;
    }
    if (!jockey_table.Contained(victoriousJockeyId) || !jockey_table.Contained(losingJockeyId)) {
        return StatusType::FAILURE;
    }


    return StatusType::FAILURE;
}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    return StatusType::FAILURE;
}

StatusType Plains::unite_by_record(int record)
{
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId){
if (jockeyId <= 0) {
    return StatusType::INVALID_INPUT;
}
    if (!jockey_table.Contained(jockeyId)) {
        return StatusType::FAILURE;
    }
    std::shared_ptr<jockey> jockey = jockey_table.getObj(jockeyId);
    return jockey->get_jockey_record();
}

output_t<int> Plains::get_team_record(int teamId){
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!Teams->Exists(teamId)) {
        return StatusType::FAILURE;
    }
    auto temp = Teams->Find(teamId);
    return temp->get_balnce_in_team();

}
