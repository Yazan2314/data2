//
// Created by yazan on 09/01/2025.
//

#include "jockey.h"

jockey::jockey(int jockeyid ,int idteam): jockey_Id(jockeyid), record(0),teamid(idteam) {}


int jockey::getJockeyId() const {
    return jockey_Id;
}


int jockey::get_jockey_record() const {
    return record;
}
void jockey::update_jockey_record(int num) {
    record += num;
}
int jockey::get_teamid() const {
    return teamid;
}




