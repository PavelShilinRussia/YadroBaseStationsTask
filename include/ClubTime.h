#ifndef TIME_H
#define TIME_H

#include <cstddef>
#include <string>
#include <iostream>

struct ClubTime {
    int hours, minutes;
    
    ClubTime();
    ClubTime(const std::string& time_str);
    
    bool operator<(const ClubTime& other) const;
    bool operator>=(const ClubTime& other) const;
    int operator-(const ClubTime& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const ClubTime& time);
};

#endif