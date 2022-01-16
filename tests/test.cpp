// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <sstream>
#include "header.hpp"

TEST(Analyser, Constructor) {
  boost::filesystem::path p;
  ASSERT_EQ(Analys{p}.getPathToFtp().string(), "..");
  boost::filesystem::path v{"../misc"};
  ASSERT_EQ(Analys{v}.getPathToFtp().string(), "../misc");
}
TEST(FinancialFile, LessOperator) {
  File lhs, rhs;
  lhs.date.year = 1;
  lhs.date.month = 1;
  lhs.date.day = 1;
  rhs.date.year = 2;
  rhs.date.month = 2;
  rhs.date.day = 2;
  EXPECT_TRUE(lhs < rhs);
}

TEST(Date, OutOperator) {
  std::stringstream ss;
  Date date;
  date.year = 5;
  date.month = 5;
  date.day = 5;
  ss << date;
  EXPECT_EQ(ss.str(), "5-5-5");
}
