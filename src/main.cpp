#include "../include/ComputerClub.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    ComputerClub club(argv[1]);
    club.process_events();

    return 0;
}