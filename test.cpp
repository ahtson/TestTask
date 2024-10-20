#include "vector.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include <initializer_list>
#include <string>

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

TEST_CASE("Handling exceptions") {
  vector<int> v({1, 2, 42, -1});
  REQUIRE_THROWS_AS(v[-1], VectorException);
  REQUIRE_THROWS_AS(v[4], VectorException);
}

TEST_CASE("Popping vector of non-generic types") {
  vector<std::string> v({"hello", "world", "!"});
  v.pop_back();
  REQUIRE(v.size() == 2);
  REQUIRE(v.back() == "world");
}

TEST_CASE("Assignment operator") {
  vector<std::string> a({"Hello", "World"});
  vector<std::string> b({"Good", "Night"});
  a = b;
  REQUIRE(a.size() == b.size());
  REQUIRE(a[0] == b[0]);
  a[0] = "Bad";
  REQUIRE(a[0] == "Bad");
  REQUIRE(b[0] == "Good");
}

TEST_CASE("std::initializer_list constructor") {
  std::initializer_list<std::string> list = {"Hello", "World", "!"};
  {
    vector<std::string> v(list);
  }
  REQUIRE(*list.begin() == "Hello");
}
