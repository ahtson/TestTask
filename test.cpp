#include "vector.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Does work") {
  vector<int> v(5);
  REQUIRE(v.size() == 0);
  REQUIRE(v.capacity() == 5);
  SECTION("Resizing") {
    v.resize(10);
    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() >= 10);
  }
}

TEST_CASE("Push, pop, front back and indexing operator") {
  vector<int> v(5);
  v.push_back(1);
  REQUIRE(v[0] == 1);
  v.push_back(2);
  v.push_back(3);
  REQUIRE(v.size() == 3);
  REQUIRE(v.front() == 1);
  REQUIRE(v.back() == 3);
  v.pop_back();
  REQUIRE(v.size() == 2);
  REQUIRE(v.back() == 2);
}

TEST_CASE("Iterator and initializing with std::initializer_list") {
  SECTION("std::initializer_list test") {
    vector<int> v({1, 2});
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
  }
  SECTION("Iterating") {
    vector<int> v({0, 1, 2, 3, 4, 5});
    auto iter = v.begin();
    REQUIRE(*iter == v.front());
    ++iter;
    REQUIRE(*iter == v[1]);
    size_t i = 0;
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
      REQUIRE(*iter == v[i]);
      ++i;
    }
  }
}
