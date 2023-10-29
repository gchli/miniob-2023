#pragma once

#include <cstdint>
#include <string>
#include "rc.h"

using namespace std;

#define DATE_STR_LENGTH 10
extern int max_days_per_month[13];
union date_u
{
  struct
  {
    uint8_t  day : 8;
    uint8_t  month : 8;
    uint16_t year : 16;
  };
  uint32_t value;
};

bool        is_leap_year();
bool        is_date_valid(int year, int month, int day);
bool        is_date_valid(const string &date_str);
RC          str_to_date(const char *date_chars, date_u &date);
RC          str_to_date(const std::string &date_chars, date_u &date);
std::string date_to_str(const date_u &date);
RC          format_to_date(const date_u &date, const string &date_format, string &date_str);