/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2023/06/28.
//

#include <cmath>
#include <cstddef>
#include <sstream>
#include "common/date.h"
#include "common/rc.h"
#include "sql/parser/value.h"
#include "storage/common/limits.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats", "booleans", "dates", "texts"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= DATES) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

Value::Value(date_u date) { set_date(date); }

Value::Value(std::size_t val) { set_text_hash(val); }

void Value::set_data(char *data, int length)
{
  null = false;
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    case DATES: {
      date_value_ = *(date_u *)data;
      length_     = length;
    } break;
    case TEXTS: {
      text_hash_ = *(size_t *)data;
      length_    = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_text_hash(size_t val)
{
  attr_type_ = TEXTS;
  text_hash_ = val;
  length_    = sizeof(val);
}

void Value::set_date(date_u d)
{
  attr_type_  = DATES;
  date_value_ = d;
  length_     = sizeof(date_u);
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATES: {
      set_date(value.get_date());
    } break;
    case TEXTS: {
      set_text_hash(value.get_text_hash());
    }
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_null() { null = true; }

bool Value::is_null() const { return null; }

const char *Value::data() const
{
  switch (attr_type_) {
    case TEXTS: {
      return (const char *)&text_hash_;
    } break;
    case CHARS: {
      return str_value_.c_str();
    } break;
    case DATES: {
      return (const char *)&date_value_;
    }
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  if (is_null()) {
    os << "NULL";
    return os.str();
  }
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATES: {
      os << date_to_str(date_value_);
    } break;
    case TEXTS: {
      os << text_hash_;
    }
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  // NULL value compare
  if (this->is_null() && other.is_null()) {
    return 0;
  }
  if (this->is_null() && !other.is_null()) {
    return -1;
  }
  if (!this->is_null() && other.is_null()) {
    return 1;
  }

  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      case DATES: {
        return common::compare_date((void *)&this->date_value_, (void *)&other.date_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  }
  // compare different types
  if (this->attr_type_ == INTS) {
    float this_data = this->num_value_.int_value_;
    if (other.attr_type_ == FLOATS) {
      return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
    }
    if (other.attr_type_ == CHARS) {
      float other_data = std::atof(other.data());
      return common::compare_float((void *)&this_data, (void *)&other_data);
    }
  } else if (this->attr_type_ == FLOATS) {
    if (other.attr_type_ == INTS) {
      float other_data = other.num_value_.int_value_;
      return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
    }
    if (other.attr_type_ == CHARS) {
      float other_data = std::atof(other.data());
      return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
    }
  } else if (this->attr_type_ == CHARS) {
    float this_data = std::atof(this->data());
    if (other.attr_type_ == INTS) {
      float other_data = other.num_value_.int_value_;
      return common::compare_float((void *)&this_data, (void *)&other_data);
    } else if (other.attr_type_ == FLOATS) {
      return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
    } else if (other.attr_type() == DATES) {
      date_u this_data;
      auto   rc = str_to_date(this->data(), this_data);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to convert string to date. s=%s", this->data());
        return -1;
      }
      return common::compare_date((void *)&this_data, (void *)&other.date_value_);
    }
  } else if (this->attr_type_ == DATES) {
    if (other.attr_type() == CHARS) {
      date_u this_data = this->date_value_;
      date_u other_data;
      auto   rc = str_to_date(other.data(), other_data);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to convert string to date. s=%s", other.data());
        return -1;
      }
      return common::compare_date((void *)&this_data, (void *)&other_data);
    } else if (other.attr_type() == INTS) {
      return common::compare_int((void *)&this->date_value_, (void *)&other.num_value_.int_value_);
    } else if (other.attr_type() == FLOATS) {
      int other_data = other.num_value_.float_value_;
      return common::compare_int((void *)&this->date_value_, (void *)&other_data);
    }
  }
  LOG_ERROR("Invalid data compare.");
  return -1;  // TODO return rc?
}

RC Value::convert_to(AttrType type)
{
  if (attr_type_ == type) {
    return RC::SUCCESS;
  }
  switch (attr_type_) {
    case FLOATS: {
      float val = get_float();
      switch (type) {
        case INTS: {
          set_int(round(val));
        } break;
        case CHARS: {
          set_string(common::double_to_str(val).c_str());
        } break;
        default: {
          LOG_WARN("Invalid convert type. type=%d", type);
          return RC::INVALID_ARGUMENT;
        }
      }
      break;
    }
    case INTS: {
      int val = get_int();
      switch (type) {
        case FLOATS: {
          set_float((float)val);
        } break;
        case CHARS: {
          set_string(std::to_string(val).c_str());
        } break;
        default: {
          LOG_WARN("Invalid convert type. type=%d", type);
          return RC::INVALID_ARGUMENT;
        }
      }
      break;
    }
    case CHARS: {
      std::string val = get_string();
      switch (type) {
        case FLOATS: {
          try {
            set_float(std::stof(val));
          } catch (std::exception const &ex) {
            LOG_WARN("Failed to convert string to int. s=%s, ex=%s", val.c_str(), ex.what());
            return RC::INVALID_ARGUMENT;
          }
        } break;
        case INTS: {
          try {
            set_int(std::stoi(val));
          } catch (std::exception const &ex) {
            LOG_WARN("Failed to convert string to int. s=%s, ex=%s", val.c_str(), ex.what());
            return RC::INVALID_ARGUMENT;
          }
        } break;
        default: {
          LOG_WARN("Invalid convert type. type=%d", type);
          return RC::INVALID_ARGUMENT;
        }
      }
      break;
    }
    default: {
      LOG_WARN("Invalid convert type. type=%d", type);
      return RC::INVALID_ARGUMENT;
    }
  }
  return RC::SUCCESS;
}

bool Value::compare_like(const Value &other) const { return common::compare_string_like(str_value_, other.str_value_); }

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }
date_u      Value::get_date() const { return date_value_; }
std::size_t Value::get_text_hash() const { return text_hash_; }
bool        Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}
