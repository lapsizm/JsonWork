// Copyright 2020 Your Name <your_email>

#include <parser.hpp>

void from_json(const nlohmann::json& j, Student& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

auto get_name(const nlohmann::json& j) -> std::string {
  if (!(j.is_string())) {
    throw std::invalid_argument("GET_NAME: Expected string-type");
  }
  return j.get<std::string>();
}

auto get_group(const nlohmann::json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_unsigned())
    return j.get<size_t>();
  else
    throw std::invalid_argument(
        "GET_GROUP: Expected string-type or unsigned integer");
}

auto get_avg(const nlohmann::json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else if (j.is_number_unsigned())
    return j.get<std::size_t>();
  else
    throw std::invalid_argument(
        "GET_AVG: Expected string-type, double or unsigned integer");
}

auto get_debt(const nlohmann::json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_array())
    return j.get<std::vector<std::string>>();
  else
    throw std::invalid_argument("GET_DEBT: Expected string-type or array");
}

std::vector<Student> parse_to_vec(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::invalid_argument("Json file is not open");
  }
  nlohmann::json data;
  file >> data;

  if (!(data["items"].is_array())) {
    throw std::invalid_argument("items is not array!");
  }
  if (data["items"].size() != (data["_meta"])["count"]) {
    throw std::invalid_argument("count in _meta doesn't match items size)");
  }

  std::vector<Student> vec_st;
  for (const nlohmann::json& item : data["items"]) {
    Student st;
    from_json(item, st);
    vec_st.push_back(st);
  }
  return vec_st;
}

std::string get_str(const std::any& str) {
  if (str.type() == typeid(std::string)) {
    return std::any_cast<std::string>(str);
  }
  if (str.type() == typeid(size_t)) {
    return std::to_string(std::any_cast<size_t>(str));
  }
  if (str.type() == typeid(double)) {
    return std::to_string(std::any_cast<double>(str));
  }
  if (str.type() == typeid(std::vector<std::string>)) {
    return std::to_string(std::any_cast<std::vector<std::string>>(str).size()) +
           " items";
  }
  return "null";
}

void print(const std::vector<Student>& students, std::ostream& os) {
  std::string table_line;
  for (size_t i = 0; i < 4; ++i) {
    table_line += "|-";
    switch (i % 4) {
      case 0:
        table_line += std::string(50, '-');
        break;
      case 1:
        table_line += std::string(20, '-');
        break;
      case 2:
        table_line += (std::string(20, '-'));
        break;
      case 3:
        table_line += (std::string(100, '-'));
        break;
    }
  }
  table_line += '|';

  os << "| " << std::left << std::setw(50) << "name";
  os << "| " << std::setw(20) << "group";
  os << "| " << std::setw(20) << "avg";
  os << "| " << std::setw(100) << "debt"
     << "|" << std::endl;
  os << table_line << std::endl;
  for (size_t i = 0; i < students.size(); ++i) {
    print(students[i], os);
    os << table_line << std::endl;
  }
}

void print(const Student& student, std::ostream& os) {
  os << "| " << std::setw(50) << student.name;
  os << "| " << std::setw(20) << get_str(student.group);
  os << "| " << std::setw(20) << get_str(student.avg);
  os << "| " << std::setw(100) << get_str(student.debt) << "|"
     << std::endl;
}