#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    List<int> cnm = List<int>();
    cnm.insertFront(77);
    cnm.insertFront(6);
    cnm.insertBack(233);
    cnm.insertBack(7);
    List<int> nmsl = List<int>();
    nmsl.insertFront(4);
    nmsl.insertFront(5);
    nmsl.insertBack(8);
    nmsl.insertBack(9);
    cnm.sort();
    nmsl.sort();
    assert(cnm.size() == 4);
    assert(nmsl.size() == 4);
    List<int>::ListIterator it(cnm.begin());
    
    REQUIRE(*it == 6);
    ++it;
    REQUIRE(*it == 7);
    ++it;
    REQUIRE(*it == 77);
    ++it;
    REQUIRE(*it == 233);
    ++it;
    REQUIRE(it == cnm.end());

    List<int>::ListIterator it2(nmsl.begin());

    REQUIRE(*it2 == 4);
    ++it2;
    REQUIRE(*it2 == 5);
    ++it2;
    REQUIRE(*it2 == 8);
    ++it2;
    REQUIRE(*it2 == 9);
    ++it2;
    REQUIRE(it2 == nmsl.end());
}
