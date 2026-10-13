#include "db_table.hpp"

#include <stdexcept>

const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    for (auto& row : rows_) {
      void** data = row.second;
      void** new_data =
          new void*[static_cast<unsigned long>(row_col_capacity_) *
                    kRowGrowthRate];
      for (size_t i = 0; i < col_descs_.size(); ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      row.second = new_data;
    }
    row_col_capacity_ *= kRowGrowthRate;
  }

  col_descs_.push_back(col_desc);

  for (auto& row : rows_) {
    switch (col_desc.second) {
    case DataType::kString:
      row.second[col_descs_.size() - 1] =
          static_cast<void*>(new std::string(""));
      break;
    case DataType::kInt:
      row.second[col_descs_.size() - 1] = static_cast<void*>(new int(0));
      break;
    case DataType::kDouble:
      row.second[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
      break;
    default:
      break;
    }
  }
}
void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size() || col_idx < 0) {
    throw std::out_of_range("col_idx is outside the range of col_descs_");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error(
        "any table with at least one row must have at least one column");
  }
  for (auto& row : rows_) {
    switch (col_descs_.at(col_idx).second) {
    case DataType::kString:
      delete static_cast<std::string*>(row.second[col_idx]);
      break;
    case DataType::kInt:
      delete static_cast<int*>(row.second[col_idx]);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(row.second[col_idx]);
      break;
    default:
      break;
    }
    for (size_t i = col_idx; i < col_descs_.size() - 1; ++i) {
      row.second[i] = row.second[i + 1];
    }
    row.second[col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}
void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("invalid");
  }
  void** new_row = new void*[row_col_capacity_];
  unsigned int id = next_unique_id_;
  rows_[id] = new_row;
  unsigned int col_index = 0;
  for (const std::string& data : col_data) {
    DataType data_type = col_descs_[col_index].second;
    switch (data_type) {
    case DataType::kString:
      new_row[col_index] = static_cast<void*>(new std::string(data));
      break;
    case DataType::kInt:
      new_row[col_index] = static_cast<void*>(new int(std::stoi(data)));
      break;
    case DataType::kDouble:
      new_row[col_index] = static_cast<void*>(new double(std::stod(data)));
      break;
    default:
      break;
    }
    ++col_index;
  }
  next_unique_id_++;
}
void DbTable::DeleteRowById(unsigned int id) {
  if (!rows_.contains(id)) {
    throw std::invalid_argument("id does not exist");
  }
  auto it = rows_.find(id);
  void** row_data = it->second;
  for (size_t i = 0; i < col_descs_.size(); ++i) {
    DataType data_type = col_descs_[i].second;
    switch (data_type) {
    case DataType::kString:
      delete static_cast<std::string*>(row_data[i]);
      break;
    case DataType::kInt:
      delete static_cast<int*>(row_data[i]);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(row_data[i]);
      break;
    default:
      throw std::invalid_argument("invalid");
    }
  }
  delete[] row_data;
  rows_.erase(it);
}
DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_) {
  col_descs_ = rhs.col_descs_;
  for (const auto& row : rhs.rows_) {
    void** new_row = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      DataType data_type = col_descs_[i].second;
      switch (data_type) {
      case DataType::kString:
        new_row[i] = new std::string(*static_cast<std::string*>(row.second[i]));
        break;
      case DataType::kInt:
        new_row[i] = new int(*static_cast<int*>(row.second[i]));
        break;
      case DataType::kDouble:
        new_row[i] = new double(*static_cast<double*>(row.second[i]));
        break;
      default:
        break;
      }
    }
    rows_[row.first] = new_row;
  }
}
DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (auto& row : rows_) {
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        delete static_cast<std::string*>(row.second[i]);
        break;
      case DataType::kInt:
        delete static_cast<int*>(row.second[i]);
        break;
      case DataType::kDouble:
        delete static_cast<double*>(row.second[i]);
        break;
      default:
        break;
      }
    }
    delete[] row.second;
  }
  rows_.clear();
  col_descs_ = rhs.col_descs_;
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  CopyRows(rhs);

  return *this;
}
DbTable::~DbTable() {
  for (auto& row : rows_) {
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        delete static_cast<std::string*>(row.second[i]);
        break;
      case DataType::kInt:
        delete static_cast<int*>(row.second[i]);
        break;
      case DataType::kDouble:
        delete static_cast<double*>(row.second[i]);
        break;
      default:
        break;
      }
    }
    delete[] row.second;
  }
}
std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (size_t i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_[i].first << "(";
    switch (table.col_descs_[i].second) {
    case DataType::kString:
      os << "std::string)";
      break;
    case DataType::kInt:
      os << "int)";
      break;
    case DataType::kDouble:
      os << "double)";
      break;
    }
    if (i < table.col_descs_.size() - 1) {
      os << ", ";
    } else {
      os << "\n";
    }
  }
  for (const auto& row : table.rows_) {
    for (size_t i = 0; i < table.col_descs_.size(); ++i) {
      switch (table.col_descs_[i].second) {
      case DataType::kString:
        os << *(static_cast<std::string*>(row.second[i]));
        break;
      case DataType::kInt:
        os << *(static_cast<int*>(row.second[i]));
        break;
      case DataType::kDouble:
        os << *(static_cast<double*>(row.second[i]));
        break;
      }
      if (i < table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}

void DbTable::CopyRows(const DbTable& rhs) {
  for (const auto& row : rhs.rows_) {
    void** new_row = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      DataType data_type = col_descs_[i].second;
      switch (data_type) {
      case DataType::kString:
        new_row[i] = new std::string(*static_cast<std::string*>(row.second[i]));
        break;
      case DataType::kInt:
        new_row[i] = new int(*static_cast<int*>(row.second[i]));
        break;
      case DataType::kDouble:
        new_row[i] = new double(*static_cast<double*>(row.second[i]));
        break;
      default:
        break;
      }
    }
    rows_[row.first] = new_row;
  }
}
