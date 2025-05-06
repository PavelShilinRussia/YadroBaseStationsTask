#include "../include/Event.h"
#include <sstream>

Event::Event(const std::string& line) {
    std::istringstream iss(line);
    std::string time_str;
    iss >> time_str >> id >> client;
    time = ClubTime(time_str);
    if (id == 2) {
        iss >> table;
    }
}

void Event::print() const {
    std::cout << time << " " << id << " " << client;
    if (id == 2 || id == 12) {
        std::cout << " " << table;
    }
    std::cout << std::endl;
}