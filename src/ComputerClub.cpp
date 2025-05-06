#include "../include/ComputerClub.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

ComputerClub::ComputerClub(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        exit(1);
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    
    validate_input(lines);
    tables.resize(num_tables);
}

void ComputerClub::validate_input(const std::vector<std::string>& lines) {
    if (lines.empty()) {
        std::cout << lines[0] << std::endl;
        exit(1);
    }
    
    try {
        num_tables = std::stoi(lines[0]);
        if (num_tables <= 0) throw std::exception();
        
        std::istringstream iss(lines[1]);
        std::string start, end;
        iss >> start >> end;
        start_time = ClubTime(start);
        end_time = ClubTime(end);
        
        hourly_rate = std::stoi(lines[2]);
        if (hourly_rate <= 0) throw std::exception();
        
        for (size_t i = 3; i < lines.size(); ++i) {
            std::istringstream event_iss(lines[i]);
            std::string time_str;
            int id;
            event_iss >> time_str >> id;
            if (id < 1 || id > 4) {
                std::cout << lines[i] << std::endl;
                exit(1);
            }
            ClubTime event_time(time_str);
            if (i > 3 && event_time < ClubTime(events[events.size()-1].time)) {
                std::cout << lines[i] << std::endl;
                exit(1);
            }
            events.emplace_back(lines[i]);
        }
    } catch (...) {
        std::cout << lines[0] << std::endl;
        exit(1);
    }
}

void ComputerClub::print_error(const ClubTime& time, const std::string& error) {
    std::cout << time << " 13 " << error << std::endl;
}

void ComputerClub::calculate_revenue(int table_idx) {
    if (tables[table_idx].is_occupied) {
        int minutes = end_time - tables[table_idx].start_time;
        tables[table_idx].occupied_time += minutes;
        int hours = (minutes + 59) / 60;
        tables[table_idx].revenue += hours * hourly_rate;
    }
}

void ComputerClub::process_events() {
    std::cout << start_time << std::endl;
    
    for (const auto& event : events) {
        event.print();
        
        if (event.time < start_time || event.time >= end_time) {
            print_error(event.time, "NotOpenYet");
            continue;
        }
        
        switch (event.id) {
            case 1:
                if (clients_in_club.count(event.client)) {
                    print_error(event.time, "YouShallNotPass");
                } else {
                    clients_in_club.insert(event.client);
                }
                break;
                
            case 2:
                if (!clients_in_club.count(event.client)) {
                    print_error(event.time, "ClientUnknown");
                } else if (tables[event.table-1].is_occupied) {
                    print_error(event.time, "PlaceIsBusy");
                } else {
                    for (auto& table : tables) {
                        if (table.is_occupied && table.client == event.client) {
                            int minutes = event.time - table.start_time;
                            table.occupied_time += minutes;
                            int hours = (minutes + 59) / 60;
                            table.revenue += hours * hourly_rate;
                            table.is_occupied = false;
                            table.client.clear();
                            break;
                        }
                    }
                    
                    tables[event.table-1].is_occupied = true;
                    tables[event.table-1].client = event.client;
                    tables[event.table-1].start_time = event.time;
                }
                break;
                
            case 3:
                if (!clients_in_club.count(event.client)) {
                    print_error(event.time, "ClientUnknown");
                } else {
                    bool has_free_table = false;
                    for (const auto& table : tables) {
                        if (!table.is_occupied) {
                            has_free_table = true;
                            break;
                        }
                    }
                    if (has_free_table) {
                        print_error(event.time, "ICanWaitNoLonger!");
                    } else if (waiting_queue.size() >= num_tables) {
                        print_error(event.time, "ICanWaitNoLonger!");
                        std::cout << event.time << " 11 " << event.client << std::endl;
                        clients_in_club.erase(event.client);
                    } else {
                        waiting_queue.push(event.client);
                    }
                }
                break;
                
            case 4:
                if (!clients_in_club.count(event.client)) {
                    print_error(event.time, "ClientUnknown");
                } else {
                    clients_in_club.erase(event.client);
                    for (auto& table : tables) {
                        if (table.is_occupied && table.client == event.client) {
                            int minutes = event.time - table.start_time;
                            table.occupied_time += minutes;
                            int hours = (minutes + 59) / 60;
                            table.revenue += hours * hourly_rate;
                            table.is_occupied = false;
                            table.client.clear();
                            
                            if (!waiting_queue.empty()) {
                                std::string waiting_client = waiting_queue.front();
                                waiting_queue.pop();
                                table.is_occupied = true;
                                table.client = waiting_client;
                                table.start_time = event.time;
                                std::cout << event.time << " 12 " << waiting_client << " " 
                                          << (&table - &tables[0] + 1) << std::endl;
                            }
                            break;
                        }
                    }
                }
                break;
        }
    }
    
    std::vector<std::string> remaining_clients(clients_in_club.begin(), clients_in_club.end());
    std::sort(remaining_clients.begin(), remaining_clients.end());
    for (const auto& client : remaining_clients) {
        std::cout << end_time << " 11 " << client << std::endl;
        for (auto& table : tables) {
            if (table.is_occupied && table.client == client) {
                calculate_revenue(&table - &tables[0]);
                table.is_occupied = false;
                table.client.clear();
            }
        }
    }
    
    std::cout << end_time << std::endl;
    
    for (size_t i = 0; i < tables.size(); ++i) {
        calculate_revenue(i);
        std::cout << i + 1 << " " << tables[i].revenue << " ";
        int hours = tables[i].occupied_time / 60;
        int minutes = tables[i].occupied_time % 60;
        std::cout << std::setfill('0') << std::setw(2) << hours << ":"
                  << std::setfill('0') << std::setw(2) << minutes << std::endl;
    }
}