#include <iostream>
#include "schedule.h"

int main() {
    V2D roster = file_to_V2D("../tests/data/c5_s10_3_roster_errors.csv");

    V2D student = file_to_V2D("../tests/data/c5_s10_3_students_errors.csv");
    
    V2D out = clean(roster, student);
  
    std::vector<std::string> timeSlots;
    int slots = 2;
    for(int i = 0; i < slots; i++){
        timeSlots.push_back(std::to_string(i));
    }
    V2D outSched = schedule(out, timeSlots);

    std::cout << "Coloring:" << std::endl;
    std::cout << "{ ";
    for (int i = 0; i < (int) outSched.size(); ++i){
        std::cout << "{ ";
        for(int j = 0; j < (int) outSched[i].size()-1; ++j){
            std::cout << outSched[i][j] << ", ";
        }
        std::cout << outSched[i][outSched[i].size()-1] << "}, \\" << std::endl;
    }
    std::cout << "}" << std::endl;
}