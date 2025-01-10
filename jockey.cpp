//
// Created by yazan on 09/01/2025.
//

#include "jockey.h"

jockey::jockey() {

}


int jockey::getJockeyId() const {
    return jockey_Id;
}


int jockey::get_jockey_record() const {
    return wins - losses;
}


