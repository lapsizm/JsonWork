// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include "parser.hpp"


TEST(Parser, meta_error) {
  EXPECT_THROW(std::vector<Student> p = parse_to_vec("../json/file3.json"),
               std::invalid_argument);
}

TEST(Parser, invalid_name) {
  EXPECT_THROW(auto p = parse_to_vec("../json/file4.json"),
               std::invalid_argument);
}

TEST(Parser, invalid_group) {
  EXPECT_THROW(auto p = parse_to_vec("../json/file5.json"),
               std::invalid_argument);
}

TEST(Parser, not_opened) {
  EXPECT_THROW(auto p = parse_to_vec("../json/fileee6.json"),
               std::invalid_argument);
}

TEST(Parser, not_array) {
  EXPECT_THROW(auto p = parse_to_vec("../json/file5.json"),
               std::invalid_argument);
}
