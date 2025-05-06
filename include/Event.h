#ifndef EVENT_H
#define EVENT_H

#include "ClubTime.h"
#include <string>
#include <iostream>

struct Event {
    ClubTime time;
    int id;
    std::string client;
    int table = 0;
    
    Event(const std::string& line);
    void print() const;
};

#endif