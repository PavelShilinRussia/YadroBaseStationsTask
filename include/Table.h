#ifndef TABLE_H
#define TABLE_H


#include <string>
#include "ClubTime.h"

struct Table {
    int revenue = 0;
    int occupied_time = 0;
    ClubTime start_time;
    bool is_occupied = false;
    std::string client;
};

#endif