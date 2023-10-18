#include "common/rc.h"
#include "date.h"
#include <cstdio>
#include <cstring>
#include <string>

int max_days_per_month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year)
{
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return true;
  }
  return false;
}

bool is_date_valid(int year, int month, int day)
{
  if (year < 0 || year > 9999)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;
  if (day > max_days_per_month[month])
    return false;
  if (!is_leap_year(year) && month == 2 && day > 28)
    return false;
  return true;
}

bool is_date_valid(const string &date_str)
{
  date_u date;
  return str_to_date(date_str, date) == RC::SUCCESS;
}

RC str_to_date(const string &date_chars, date_u &date) { return str_to_date(date_chars.c_str(), date); }

RC str_to_date(const char *date_chars, date_u &date)
{
  if (strlen(date_chars) > DATE_STR_LENGTH) {
    return RC::INVALID_ARGUMENT;
  }
  int year, month, day;
  int ret = sscanf(date_chars, "%d-%d-%d", &year, &month, &day);
  if (ret != 3) {
    return RC::INVALID_ARGUMENT;
  }
  if (!is_date_valid(year, month, day)) {
    return RC::INVALID_ARGUMENT;
  }
  date.year  = year;
  date.month = month;
  date.day   = day;
  return RC::SUCCESS;
}

std::string date_to_str(const date_u &date)
{
  char data_chars[DATE_STR_LENGTH + 1];
  // std::format
  sprintf(data_chars, "%04d-%02d-%02d", date.year, date.month, date.day);
  return string(data_chars);
}