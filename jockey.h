//
// Created by yazan on 09/01/2025.
//

#ifndef JOCKEY_H
#define JOCKEY_H
#include<memory>
#include "team.h"

class jockey {
    int jockey_Id;
    int wins;
    int losses;
    std::shared_ptr<team> team;

    public:
    jockey(int jockeyId);
    ~jockey();
    int getJockeyId() const;
    int get_jockey_record() const;


};



#endif //JOCKEY_H
