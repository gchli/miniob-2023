#include "common/date.h"
#include "gtest/gtest.h"
#include <iterator>

TEST(date_tools, test_date_tools)
{
  const char *date1 = "1234-05-06";
  RC          ret;
  date_u      date;
  ret = str_to_date(date1, date);
  ASSERT_EQ(ret, RC::SUCCESS);
  cout << date_to_str(date) << endl;

  const char *date2 = "1234-5-06";
  ret               = str_to_date(date2, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);

  const char *date3 = "1234-05-6";
  ret               = str_to_date(date3, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);

  const char *date4 = "12345-06-07";
  ret               = str_to_date(date4, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
  const char *date5 = "1234-00-01";
  ret               = str_to_date(date5, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
  const char *date6 = "1234-13-01";
  ret               = str_to_date(date6, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
  const char *date7 = "1234-05-00";
  ret               = str_to_date(date7, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
  const char *date8 = "1234-05-32";
  ret               = str_to_date(date8, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
  const char *date9 = "-1-05-06";
  ret               = str_to_date(date9, date);
  ASSERT_EQ(ret, RC::INVALID_ARGUMENT);
}

int main(int argc, char **argv)
{
  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}