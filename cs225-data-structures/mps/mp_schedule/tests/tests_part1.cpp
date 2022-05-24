#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "schedule.h"
#include "tests_helper.h"

using namespace cs225;

#define CS225_SOLUTION

TEST_CASE("file_to_V2D Public Test 1", "[weight=5]") {
    V2D roster = file_to_V2D("../tests/data/c5_s10_3_roster.csv");

    V2D ans = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    exactV2D(roster, ans);

    V2D students = file_to_V2D("../tests/data/c5_s10_3_students.csv");

    ans = {
        {"JydY", "CS577"}, \
        {"MnWd", "CS577", "CS500", "CS395"}, \
        {"tnkL", "CS577", "CS591"}, \
        {"gpDS", "CS591", "CS395"}, \
        {"94Ol", "CS591"}, \
        {"SjC0", "CS386"}, \
        {"EYge", "CS386", "CS500", "CS395"}, \
        {"Nvu1", "CS386"}, \
        {"uAcT", "CS500"}
        };

    exactV2D(students, ans);
}

TEST_CASE("file_to_V2D Public Test 2", "[weight=5]") {
    V2D roster = file_to_V2D("../tests/data/c10_s50_2_roster.csv");

    V2D ans = {
        {"CS502", "RAq7", "4GUp"}, \
        {"CS512", "nEFp", "n4mr"}, \
        {"CS161", "n4mr", "gLbj"}, \
        {"CS259", "rJvt", "RAq7"}, \
        {"CS411", "OZOR", "nHTn"}, \
        {"CS299", "3p9F", "xrmC"}, \
        {"CS190", "STSG", "3p9F"}, \
        {"CS180", "ZFvu", "Mkds"}, \
        {"CS583", "UkhY", "Xxka"}, \
        {"CS245", "RAq7", "t57x"}
        };

    exactV2D(roster, ans);

    V2D students = file_to_V2D("../tests/data/c10_s50_2_students.csv");

    ans = {
        {"RAq7", "CS502", "CS259", "CS245"}, \
        {"4GUp", "CS502"}, \
        {"nEFp", "CS512"}, \
        {"n4mr", "CS512", "CS161"}, \
        {"gLbj", "CS161"}, \
        {"rJvt", "CS259"}, \
        {"OZOR", "CS411"}, \
        {"nHTn", "CS411"}, \
        {"3p9F", "CS299", "CS190"}, \
        {"xrmC", "CS299"}, \
        {"STSG", "CS190"}, \
        {"ZFvu", "CS180"}, \
        {"Mkds", "CS180"}, \
        {"UkhY", "CS583"}, \
        {"Xxka", "CS583"}, \
        {"t57x", "CS245"}
        };

    exactV2D(students, ans);
}

TEST_CASE("clean() Public Test 1", "[weight=5]") {
    V2D students = {
    {"JydY", "CS577"}, \
    {"MnWd", "CS577", "CS395"}, \
    {"tnkL", "CS577", "CS591"}, \
    {"gpDS", "CS591", "CS395"}, \
    {"94Ol", "CS591"}, \
    {"EYge", "CS500", "CS395"}, \
    {"Nvu1", "CS386"}, \
    {"uAcT", "CS500"}
    };

    V2D roster = {
    {"CS577", "JydY", "MnWd", "tnkL"}, \
    {"CS591", "gpDS", "94Ol", "tnkL"}, \
    {"CS386", "SjC0"}, \
    {"CS500", "MnWd", "uAcT", "EYge"}, \
    {"CS395", "gpDS", "EYge", "MnWd"}
    };

    V2D ans = {{ "CS577", "JydY", "MnWd", "tnkL"}, \
    { "CS591", "gpDS", "94Ol", "tnkL"}, \
    { "CS500", "uAcT", "EYge"}, \
    { "CS395", "gpDS", "EYge", "MnWd"}};

    V2D user = clean(roster, students);

    exactV2D(user, ans);
}

TEST_CASE("clean() Public Test 2", "[weight=5]") {
    V2D students = {
    {"RAq7", "CS502", "CS259", "CS245"}, \
    {"4GUp", "CS502"}, \
    {"n4mr", "CS512"}, \
    {"gLbj", "CS161"}, \
    {"rJvt", "CS259"}, \
    {"OZOR", "CS411"}, \
    {"nHTn", "CS411"}, \
    {"3p9F", "CS299", "CS190"}, \
    {"xrmC", "CS299"}, \
    {"STSG", "CS190"}, \
    {"Mkds", "CS180"}, \
    {"UkhY", "CS583"}, \
    {"t57x", "CS245"}
    };
    
    V2D roster = {
    {"CS259", "rJvt", "RAq7"}, \
    {"CS502", "RAq7"}, \
    {"CS512", "nEFp", "n4mr"}, \
    {"CS161", "n4mr"}, \
    {"CS411", "OZOR", "nHTn"}, \
    {"CS299"}, \
    {"CS190", "STSG", "3p9F"}, \
    {"CS180", "Mkds"}, \
    {"CS583", "UkhY", "Xxka"}, \
    {"CS245", "RAq7", "abc5"}
    };

    V2D ans = {{ "CS259", "rJvt", "RAq7"}, \
    { "CS502", "RAq7"}, \
    { "CS512", "n4mr"}, \
    { "CS411", "OZOR", "nHTn"}, \
    { "CS190", "STSG", "3p9F"}, \
    { "CS180", "Mkds"}, \
    { "CS583", "UkhY"}, \
    { "CS245", "RAq7"}};

    V2D user = clean(roster, students);

    exactV2D(user, ans);
}


// TEST_CASE("schedule() Approximate Public Test 1", "[weight=2]") {
//     V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
//      {"CS591", "gpDS", "94Ol", "tnkL"}, \
//      {"CS386", "SjC0", "EYge", "Nvu1"}, \
//      {"CS500", "MnWd", "uAcT", "EYge"}, \
//      {"CS395", "gpDS", "EYge", "MnWd"}
//      };

//     std::vector<std::string> timeslots = {"9AM", "11AM", "1PM", "3PM"};

//     V2D out = schedule(roster, timeslots);

//     validColoring(roster, out, 4);
// }

// TEST_CASE("schedule() Public Test 1", "[weight=3]") {
//     V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
//      {"CS591", "gpDS", "94Ol", "tnkL"}, \
//      {"CS386", "SjC0", "EYge", "Nvu1"}, \
//      {"CS500", "MnWd", "uAcT", "EYge"}, \
//      {"CS395", "gpDS", "EYge", "MnWd"}
//      };

//     std::vector<std::string> timeslots = {"9AM", "11AM", "1PM"};

//     V2D out = schedule(roster, timeslots);

//     validColoring(roster, out, 3);
// }

// TEST_CASE("schedule() No Match Test Public 1", "[weight=5]") {
//     V2D roster = {
//     {"CS101", "a", "b"}, \
//     {"CS102", "b", "c"}, \
//     {"CS103", "a", "c"}
//     };

//     std::vector<std::string> timeslots = {"9AM", "11AM"};

//     V2D out = schedule(roster, timeslots);

//     REQUIRE(out.size()==1);
//     REQUIRE(out[0].size()==1);
//     REQUIRE(out[0][0]=="-1");
// }

