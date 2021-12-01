// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include <any>
#include <cmath>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

struct table {
  size_t name_length;
  size_t group_length;
  size_t avg_length;
  size_t debt_length;
};

auto get_name(const nlohmann::json& j) -> std::string;
auto get_group(const nlohmann::json& j) -> std::any;
auto get_avg(const nlohmann::json& j) -> std::any;
auto get_debt(const nlohmann::json& j) -> std::any;
void from_json(const nlohmann::json& j, Student& s);
std::vector<Student> parse_to_vec(const std::string& path);

std::string get_str(const std::any& str);
void print(const std::vector<Student>& students, std::ostream& os);
void print(const Student& student, std::ostream& os);

#endif  // INCLUDE_PARSER_HPP_
