#define BOOST_TEST_MODULE sv_list

#include <boost/test/included/unit_test.hpp>
#include "string_view_list.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestStringViewList)

BOOST_AUTO_TEST_CASE(Empty) {
    string_view_list list;
    BOOST_REQUIRE(list.size() == 0);
    BOOST_REQUIRE(list == "");
}

BOOST_AUTO_TEST_CASE(AddStringView) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + (str2 + str3);
    BOOST_REQUIRE(list.size() == 4);
    BOOST_REQUIRE(list[0] == '1');
    BOOST_REQUIRE(list[1] == '2');
    BOOST_REQUIRE(list[2] == '3');
    BOOST_REQUIRE(list[3] == '4');
    BOOST_CHECK_THROW(list[4], std::out_of_range);
    BOOST_REQUIRE(list == "1234");
    BOOST_REQUIRE(list.to_string() == "1234");
    BOOST_REQUIRE(list != "123");
}

BOOST_AUTO_TEST_CASE(AddStringView2) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";

    string_view_list list;
    list += str1;
    BOOST_REQUIRE(list == "1");
    list += str2;
    BOOST_REQUIRE(list == "123");
}

BOOST_AUTO_TEST_CASE(AddLists) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";

    std::string_view str3 = "4";
    std::string_view str4 = "56";

    std::string_view list_str = "123456";

    string_view_list list1 = str1 + str2;
    string_view_list list2 = str3 + str4;
    string_view_list list3 = str3;

    string_view_list list = list1 + list2;
    BOOST_REQUIRE(list1 == "123");
    BOOST_REQUIRE(list2 == "456");
    BOOST_REQUIRE(list == list_str);

    list1 += list3;
    BOOST_REQUIRE(list1 == "1234");
    BOOST_REQUIRE(list == list_str);
}

BOOST_AUTO_TEST_CASE(CompareLists) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";

    std::string_view str3 = "12";
    std::string_view str4 = "3";

    string_view_list list1 = str1 + str2;
    string_view_list list2 = str3 + str4;
    string_view_list list3 = str1 + str3;
    BOOST_REQUIRE(list1 == list2);
    BOOST_REQUIRE(list1 != list3);
}

BOOST_AUTO_TEST_CASE(Ostream) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + str2 + str3;

    std::ostringstream ss;
    ss << list;
    BOOST_REQUIRE(ss.str() == "1234");
}

BOOST_AUTO_TEST_CASE(StartsWith) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + str2 + str3;
    BOOST_REQUIRE(list.starts_with("1"));
    BOOST_REQUIRE(list.starts_with("12"));
    BOOST_REQUIRE(list.starts_with("123"));
    BOOST_REQUIRE(list.starts_with("1234"));
    BOOST_REQUIRE(!list.starts_with("12345"));
    BOOST_REQUIRE(!list.starts_with("2"));
}

BOOST_AUTO_TEST_CASE(EndsWith) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + str2 + str3;
    BOOST_REQUIRE(list.ends_with("4"));
    BOOST_REQUIRE(list.ends_with("34"));
    BOOST_REQUIRE(list.ends_with("234"));
    BOOST_REQUIRE(list.ends_with("1234"));
    BOOST_REQUIRE(!list.ends_with("01234"));
    BOOST_REQUIRE(!list.ends_with("5"));
}

BOOST_AUTO_TEST_CASE(Substr) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + str2 + str3;

    BOOST_REQUIRE(list.substr(0) == "1234");
    BOOST_REQUIRE(list.substr(1) == "234");
    BOOST_REQUIRE(list.substr(2) == "34");
    BOOST_REQUIRE(list.substr(3) == "4");
    BOOST_REQUIRE(list.substr(4) == "");

    BOOST_REQUIRE(list.substr(0, 0) == "");
    BOOST_REQUIRE(list.substr(0, 1) == "1");
    BOOST_REQUIRE(list.substr(0, 2) == "12");
    BOOST_REQUIRE(list.substr(0, 3) == "123");
    BOOST_REQUIRE(list.substr(0, 4) == "1234");
    BOOST_REQUIRE(list.substr(0, 5) == "1234");

    BOOST_REQUIRE(list.substr(1, 1) == "2");
    BOOST_REQUIRE(list.substr(1, 2) == "23");
    BOOST_REQUIRE(list.substr(1, 3) == "234");
    BOOST_REQUIRE(list.substr(1, 4) == "234");

    BOOST_REQUIRE(list.substr(2, 1) == "3");
    BOOST_REQUIRE(list.substr(2, 2) == "34");
    BOOST_REQUIRE(list.substr(2, 3) == "34");

    BOOST_REQUIRE(list.substr(3, 1) == "4");
    BOOST_REQUIRE(list.substr(3, 2) == "4");
}

BOOST_AUTO_TEST_CASE(Iterator) {
    std::string_view str1 = "1";
    std::string_view str2 = "23";
    std::string_view str3 = "4";

    string_view_list list = str1 + str2 + str3;

    string_view_list::iterator it = list.begin();
    BOOST_REQUIRE(*it == '1');
    BOOST_REQUIRE(*(++it) == '2');
    BOOST_REQUIRE(*(++it) == '3');
    BOOST_REQUIRE(*(++it) == '4');
    BOOST_REQUIRE(++it == list.end());

    std::string result_str;
    for (const char& ch : list) {
        result_str += ch;
    }

    BOOST_REQUIRE(result_str == "1234");
}

BOOST_AUTO_TEST_SUITE_END()