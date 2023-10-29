#include "common/rc.h"
#include "date.h"
#include <cstdio>
#include <cstring>
#include <sstream>
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

RC format_to_date(const date_u &date, const string &date_format, string &date_str)
{
  int               year = date.year, month = date.month, day = date.day;
  std::stringstream ss;
  string            month_string[12] = {"January",
                 "February",
                 "March",
                 "April",
                 "May",
                 "June",
                 "July",
                 "August",
                 "September",
                 "October",
                 "November",
                 "December"};
  std::string       day_postfix[31]  = {"st",
             "nd",
             "rd",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",  // 1-10
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",  // 11-20
             "st",
             "nd",
             "rd",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",
             "th",  // 21-30
             "st"};

  for (size_t i = 0; i < date_format.size();) {
    if (date_format[i] == '%') {
      if (i == date_format.size() - 1) {
        continue;
      }
      auto next_char = date_format[i + 1];
      if (next_char == 'Y') {
        ss << year;
      } else if (next_char == 'y') {
        if (year % 100 < 10) {
          ss << "0";
        }
        ss << year % 100;
      } else if (next_char == 'M') {
        ss << month_string[month - 1];
      } else if (next_char == 'm') {
        if (month < 10) {
          ss << "0";
        }
        ss << month;
      } else if (next_char == 'D') {
        ss << day << day_postfix[day - 1];
      } else if (next_char == 'd') {
        if (day < 10) {
          ss << "0";
        }
        ss << day;
      } else {
        // ss << date_format[i];
        i++;
        continue;
      }
      i += 2;
    } else {
      ss << date_format[i];
      i++;
    }
  }
  date_str = ss.str();
  return RC::SUCCESS;
}