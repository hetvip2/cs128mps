#include "db.hpp"

#include <stdexcept>

void Database::CreateTable(const std::string& table_name) {
  tables_[table_name] = new DbTable();
}
void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("invalid");
  }
  delete tables_[table_name];
  tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("invalid");
  }
  return *tables_[table_name];
}
Database::Database(const Database& rhs) {
  for (const auto& [name, table] : rhs.tables_) {
    tables_[name] = new DbTable(*table);
  }
}
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) return *this;
  for (auto& table_pair : tables_) {
    delete table_pair.second;
  }
  tables_.clear();
  for (const auto& table_pair : rhs.tables_) {
    const std::string& table_name = table_pair.first;
    const DbTable* rhs_table = table_pair.second;
    auto* new_table = new DbTable(*rhs_table);
    tables_[table_name] = new_table;
  }

  return *this;
}

Database::~Database() {
  for (auto const& [key, value] : tables_) {
    delete value;
  }
}
std::ostream& operator<<(std::ostream& os, const Database& db) {
  for (const auto& [name, table] : db.tables_) {
    os << name << "\n";
    os << table << "\n";
  }
  return os;
}