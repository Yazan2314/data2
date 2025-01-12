//
// Created by yazan on 09/01/2025.
//

#ifndef JOCKEY_H
#define JOCKEY_H

#include "team.h"

class jockey {
    int jockey_Id;
    int record;
    int teamid;
    // std::shared_ptr<team> team; // todo :i thinck no need

    public:
    jockey(int jockeyId,int team_id);
    ~jockey() = default;

    int getJockeyId() const;
    int get_jockey_record() const;
    void update_jockey_record(int num);
    int get_teamid() const;


};



#endif //JOCKEY_H
