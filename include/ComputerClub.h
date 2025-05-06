#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include "Table.h"
#include "Event.h"
#include "ClubTime.h"
#include <vector>
#include <queue>
#include <set>
#include <string>

class ComputerClub {
private:
    int num_tables;
    ClubTime start_time, end_time;
    int hourly_rate;
    std::vector<Table> tables;
    std::set<std::string> clients_in_club;
    std::queue<std::string> waiting_queue;
    std::vector<Event> events;

    void validate_input(const std::vector<std::string>& lines);
    void print_error(const ClubTime& time, const std::string& error);
    void calculate_revenue(int table_idx);

public:
    ComputerClub(const std::string& filename);
    void process_events();
};

#endif