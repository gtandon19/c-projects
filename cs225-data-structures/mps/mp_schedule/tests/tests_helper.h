#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "schedule.h"
#include <catch2/catch_test_macros.hpp>

using namespace cs225;

void validColoring(V2D rosterList, V2D color, unsigned maxColor){
    
    std::map<std::string, std::string> nodeInfo;

    for(auto & time : color){
        for(unsigned long i = 1; i < time.size(); i++){
            nodeInfo[time[i]]= time[0]; 
           // std::cout << time[0] << " " << time[i] << std::endl;
        }
    }
    
    std::set<std::string> mc;
    std::map<std::string, std::set<std::string> > sMap; 
    for(auto & row : rosterList){
        std::string course = row[0];
        std::set<std::string> ts;
        for(unsigned long i = 1; i < row.size(); i++){
            std::string student = row[i];
            std::string tcolor = nodeInfo[course];
            
            if(sMap[student].count(tcolor)!=0){
                UNSCOPED_INFO("Course " + course + " has an edge with student " \
                + student + " that are both labeled " + tcolor);
            }

            REQUIRE(sMap[student].count(tcolor)==0);
            sMap[student].insert(tcolor);
            mc.insert(tcolor);
            //std::cout << tcolor << " " << mc.size() << std::endl;
        }
    }
    
    INFO("Number of unique colors in coloring exceeds allowable.");
    REQUIRE(mc.size() <= maxColor);
}

// When we want a perfect mirroring of the answer
void exactV2D(V2D user, V2D ans){
    if(user.size() != ans.size()){UNSCOPED_INFO("V2D has incorrect number of rows."); }
    REQUIRE(user.size() == ans.size());
    for(unsigned i = 0; i < user.size(); i++){
        if(user[i].size()!=ans[i].size() ) { UNSCOPED_INFO("V2D has incorrect number of columns at row " + std::to_string(i));}
        REQUIRE(user[i].size()==ans[i].size());
        for(unsigned j = 0; j < user[i].size(); j++){
            if( user[i][j]!=ans[i][j]){ UNSCOPED_INFO("Incorrect value at i=" + std::to_string(i) + ", j=" + std::to_string(j)); }
            REQUIRE(user[i][j]==ans[i][j]);
        }
    }
}