// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include "record.h"


Plains::Plains(){
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

     auto temp = Teams->Maketeams(teamId);
        if (temp == nullptr) {
            return StatusType::FAILURE;
        }
        // records_table.addobj2(0,teamId,temp,&team::get_record);
        if (!records_table.Contained(0)) {
            std::shared_ptr<record> new_record = make_shared<record>(0);
            records_table.addObj(0,new_record);
            new_record->add_team(temp);
        }
        auto tble_of_record =records_table.getObj(0);

        tble_of_record->add_team(temp);


    }catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
      return StatusType::SUCCESS;

}

StatusType Plains::add_jockey(int jockeyId, int teamId){
if (teamId <= 0 || jockeyId <= 0) {
    return StatusType::INVALID_INPUT;
}
    if (jockey_table.Contained(jockeyId)) {
        return StatusType::FAILURE;
    }
    auto team = Teams->m_teams[teamId];
    if (team == nullptr || !team->is_Active()) {
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
    auto victoriousJockey = jockey_table.getObj(victoriousJockeyId);
    auto losingJockey = jockey_table.getObj(losingJockeyId);


    auto victoryteam = Teams->Find(victoriousJockey->get_teamid());
    auto losingteam = Teams->Find(losingJockey->get_teamid());

    if (victoryteam == nullptr || losingteam == nullptr || victoryteam == losingteam) {
        return StatusType::FAILURE;
    }
    victoriousJockey->update_jockey_record(1);
    losingJockey->update_jockey_record(-1);
    victoryteam->update_record(1);
    losingteam->update_record(-1);
    //// todo : this for union by record

    // if (!records_table.Contained(abs(victoryteam->get_record()) - 1) ) {
    //     return StatusType::FAILURE;
    // }
    //
    // auto recordwin_past = records_table.getObj(abs(victoryteam->get_record() - 1));
    // if (recordwin_past == nullptr) {
    //     return StatusType::FAILURE;
    // }
    // recordwin_past->remove_team(victoryteam);


    // if (!records_table.Contained(abs(losingteam->get_record()) + 1) ) {
    //     return StatusType::FAILURE;
    // }
    // auto recordlose_past = records_table.getObj(abs(losingteam->get_record() +1));
    // if (recordlose_past == nullptr) {
    //     return StatusType::FAILURE;
    // }
    // recordlose_past->remove_team(losingteam);


    if (!records_table.Contained(abs(victoryteam->get_record()))  ) {
        std::shared_ptr<record> new_record = make_shared<record>(abs(victoryteam->get_record()));
        records_table.addObj(abs(victoryteam->get_record()),new_record);
        new_record->add_team(victoryteam);
    }
    auto recordwin = records_table.getObj(abs(victoryteam->get_record()) );
    if (recordwin == nullptr) {
        return StatusType::FAILURE;
    }
    recordwin->add_team(victoryteam);


    if (!records_table.Contained(abs(losingteam->get_record()))) {
        std::shared_ptr<record> new_record = make_shared<record>(abs(losingteam->get_record()));
        records_table.addObj(abs(losingteam->get_record()),new_record);
        new_record->add_team(losingteam);
    }
    auto recordlost = records_table.getObj(abs(losingteam->get_record()));
   if (recordlost == nullptr) {
       return StatusType::FAILURE;
   }
    recordlost->add_team(losingteam);






    // records_table.deleteObj(abs(victoryteam->get_record() -1) , victoryteam->get_team_id());
    // records_table.deleteObj(abs(losingteam->get_record() + 1 ), losingteam->get_team_id());
    // records_table.addobj2(abs(victoryteam->get_record()) ,victoryteam->get_team_id() , victoryteam,&team::get_record);
    // records_table.addobj2(abs(losingteam->get_record()),losingteam->get_team_id()  , losingteam,&team::get_record );


    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2){
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    if (!Teams->m_teams.Contained(teamId1) || !Teams->m_teams.Contained(teamId2)) {
        return StatusType::FAILURE;
    }
    auto team1 = Teams->m_teams.getObj(teamId1);
    auto team2 = Teams->m_teams.getObj(teamId2);
    if (team1 == nullptr || team2 == nullptr) {
        return StatusType::FAILURE;
    }
    if (!team1->is_Active()||!team2->is_Active()) {
        return StatusType::FAILURE;
    }

    ////// todo : test only
    // records_table.deleteObj(abs(team1->get_record())  , teamId1);
    // records_table.deleteObj(abs(team2->get_record() ) , teamId2);
    ////////
    // int temp1 = team1->get_record();
    // int temp2 = team2->get_record();





    try {
        Teams->Union(teamId1, teamId2);

        ////// todo : test only
        // records_table.addobj2(abs(team1->get_record()), teamId1 , team1,&team::get_record);
        // records_table.addobj2(abs(team2->get_record()),teamId2  , team2,&team::get_record);
        ///////////
    }catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }

    if (!records_table.Contained(abs(team1->get_record()))) {
        std::shared_ptr<record> new_record = make_shared<record>(abs(team1->get_record()));
        records_table.addObj(abs(team1->get_record()),new_record);
        new_record->add_team(team1);
    }

    auto record1 = records_table.getObj(abs(team1->get_record()));

    record1->add_team(team1);

    if (!records_table.Contained(abs(team2->get_record()))) {
        std::shared_ptr<record> new_record = make_shared<record>(abs(team2->get_record()));
        records_table.addObj(abs(team2->get_record()),new_record);
        new_record->add_team(team2);
    }
    auto record2 = records_table.getObj(abs(team2->get_record()));

    record2->add_team(team2);







    return StatusType::SUCCESS;

}

StatusType Plains::unite_by_record(int record){
if (record <= 0) {
    return StatusType::INVALID_INPUT;
}

    if (!records_table.Contained(record)) {
        return StatusType::FAILURE;
    }
    auto record_plus = records_table.getObj(record);
    auto record_minus = records_table.getObj(record );
    if (record_minus == nullptr || record_plus == nullptr) {
        return StatusType::FAILURE;
    }

    auto tree_plus =record_plus->get_teams_tree();
    auto tree_minus =record_minus->get_teams_tree();
    int team1Id = find_plus_record_team(tree_plus.m_root,record);
    int team2Id = find_plus_record_team(tree_minus.m_root,-record);
    if (team1Id <= 0 || team2Id <= 0) {
        return StatusType::FAILURE;
    }
    // if (team1Id == -1 ||  team2Id == -1) {
    //     return StatusType::FAILURE;
    // }
    return merge_teams(team1Id, team2Id);
//
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
    auto team = Teams->m_teams[teamId];
    if (team == nullptr || !team->is_Active()) {
        return StatusType::FAILURE;
    }
    return team->get_record();

}
