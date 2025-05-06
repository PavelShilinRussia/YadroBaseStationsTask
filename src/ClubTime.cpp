#include "../include/ClubTime.h"
#include <iomanip>

ClubTime::ClubTime() : hours(0), minutes(0) {}

ClubTime::ClubTime(const std::string& time_str) {
    hours = std::stoi(time_str.substr(0, 2));
    minutes = std::stoi(time_str.substr(3, 2));
}

bool ClubTime::operator<(const ClubTime& other) const {
    return hours * 60 + minutes < other.hours * 60 + other.minutes;
}

bool ClubTime::operator>=(const ClubTime& other) const {
    return !(*this < other);
}

int ClubTime::operator-(const ClubTime& other) const {
    return (hours * 60 + minutes) - (other.hours * 60 + other.minutes);
}

std::ostream& operator<<(std::ostream& os, const ClubTime& time) {
    os << std::setfill('0') << std::setw(2) << time.hours << ":"
       << std::setfill('0') << std::setw(2) << time.minutes;
    return os;
}