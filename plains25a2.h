// 
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PLAINS25WINTER_WET1_H_
#define PLAINS25WINTER_WET1_H_



#include "hashTable.h"
#include "jockey.h"
#include "UnionFind.h"
#include "wet2util.h"
#include <memory>

#include "record.h"

class Plains {
private:
    //
    // Here you may add anything you want
    //


    HashTable<std::shared_ptr<jockey>> jockey_table;
    UnionFind* Teams;
    HashTable<std::shared_ptr<record>> records_table;
    // HashTable<team*> records_table; // for the function unitedbyrenk to keep time complixity low

    int find_plus_record_team_aux(TreeNode<int,std::shared_ptr<team>>* node , int& count , int& team_id ,int record) {
        if (node == nullptr) {
            return -1;
        }
        if (find_plus_record_team_aux(node->m_left, count, team_id,record) == -1 && count > 1) {
            return -1;  // Early exit if more than one horse has no followers
        }

        auto current = node->data;

        if (current->get_record() == record && current->is_Active() == true) {
            count++;
            team_id = current->get_team_id();
        }
        if (count > 1) {
            return -1;  // If more than one horse has no followers, return -1
        }

        if (find_plus_record_team_aux(node->m_right, count, team_id,record) == -1 && count > 1) {
            return -1;  // Early exit if more than one horse has no followers
        }

        return team_id;


    }

    int find_plus_record_team(TreeNode<int,std::shared_ptr<team>>* root, int record) {
        int count = 0;
        int team_id = -1;

        int result = find_plus_record_team_aux(root, count, team_id ,  record);
        if (count != 1) {
            return -1;
        }
        return result;


    }

    int abs(int x) {
        if (x < 0) {
            return -x;
        }
        return x;
    }




    
public:
    // <DO-NOT-MODIFY> {
    Plains();

    ~Plains();

    StatusType add_team(int teamId);

    StatusType add_jockey(int jockeyId, int teamId);

    StatusType update_match(int victoriousJockeyId, int losingJockeyId);

    StatusType merge_teams(int teamId1, int teamId2);

    StatusType unite_by_record(int record);

    output_t<int> get_jockey_record(int jockeyId);

    output_t<int> get_team_record(int teamId);
    // } </DO-NOT-MODIFY>
};

#endif // PLAINS25WINTER_WET1_H_
