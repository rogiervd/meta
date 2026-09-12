/*
Copyright 2013, 2015 Rogier van Dalen.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#define BOOST_TEST_MODULE test_meta_count_c
#include <boost/test/unit_test.hpp>

#include "meta/count_c.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_count_c)

BOOST_AUTO_TEST_CASE (meta_count_c_detail_highest_bit_index) {
    using namespace meta::count_c_detail;
    static_assert (highest_bit_index <0>::value == 0, "");
    static_assert (highest_bit_index <1>::value == 1, "");
    static_assert (highest_bit_index <2>::value == 2, "");
    static_assert (highest_bit_index <3>::value == 2, "");
    static_assert (highest_bit_index <4>::value == 3, "");
    static_assert (highest_bit_index <5>::value == 3, "");
    static_assert (highest_bit_index <6>::value == 3, "");
    static_assert (highest_bit_index <7>::value == 3, "");
    static_assert (highest_bit_index <8>::value == 4, "");
    static_assert (highest_bit_index <9>::value == 4, "");

    static_assert (highest_bit_index <127>::value == 7, "");
    static_assert (highest_bit_index <128>::value == 8, "");

    static_assert (highest_bit_index <2345>::value == 12, "");
}

BOOST_AUTO_TEST_CASE (test_meta_count_c_detail_count_pow_2) {
    using namespace meta::count_c_detail;
    using meta::size_t_vector;
    BOOST_MPL_ASSERT ((std::is_same <
        count_pow_2 <0>::type, size_t_vector <0>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_pow_2 <1>::type, size_t_vector <0, 1>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_pow_2 <3>::type, size_t_vector <0, 1, 2, 3, 4, 5, 6, 7>>));
}

BOOST_AUTO_TEST_CASE (test_meta_count_c_detail_concatenate_counts) {
    using namespace meta::count_c_detail;
    using meta::size_t_vector;

    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts<>::type, size_t_vector<>>));

    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts <size_t_vector <0>>::type, size_t_vector <0>>));
    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts <size_t_vector <0, 1>>::type,
        size_t_vector <0, 1>>));

    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts <size_t_vector <0>, size_t_vector <0, 1, 2>
        >::type, size_t_vector <0, 1, 2, 3>>));
    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts <size_t_vector <0, 1, 2, 3>, size_t_vector <0, 1>
        >::type, size_t_vector <0, 1, 2, 3, 4, 5>>));
    BOOST_MPL_ASSERT ((std::is_same <
        concatenate_counts <size_t_vector <0, 1>,
            size_t_vector <0, 1, 2, 3>, size_t_vector <0, 1>
        >::type, size_t_vector <0, 1, 2, 3, 4, 5, 6, 7>>));
}

BOOST_AUTO_TEST_CASE (test_meta_count_c_detail_count_from_zero) {
    using namespace meta::count_c_detail;
    using meta::size_t_vector;

    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <0>::type, size_t_vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <1>::type, size_t_vector <0>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <3>::type, size_t_vector <0, 1, 2>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <7>::type, size_t_vector <0, 1, 2, 3, 4, 5, 6>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <22>::type, size_t_vector <
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <23>::type, size_t_vector <
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_from_zero <173>::type, size_t_vector <
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
        50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
        70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
        90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
        110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
        120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
        140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
        150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
        170, 171, 172>>));
}

BOOST_AUTO_TEST_CASE (test_meta_count_c_detail_add_offset) {
    using namespace meta::count_c_detail;
    using meta::size_t_vector;

    BOOST_MPL_ASSERT ((std::is_same <
        add_offset <size_t_vector<>, 0>::type, size_t_vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <
        add_offset <size_t_vector<>, 4>::type, size_t_vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <
        add_offset <size_t_vector <4, 2, 7>, 5>::type,
            size_t_vector <9, 7, 12>>));
}

BOOST_AUTO_TEST_CASE (test_meta_count_c) {
    using namespace meta;

    // Without start.
    BOOST_MPL_ASSERT ((std::is_same <count_c <0>::type, size_t_vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <count_c <1>::type, size_t_vector <0>>));
    BOOST_MPL_ASSERT ((std::is_same <count_c <2>::type, size_t_vector <0, 1>>));
    BOOST_MPL_ASSERT ((std::is_same <count_c <4>::type,
        size_t_vector <0, 1, 2, 3>>));

    // With start.
    BOOST_MPL_ASSERT ((std::is_same <
        count_c <0, 0>::type, size_t_vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_c <3, 3>::type, size_t_vector<>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_c <0, 1>::type, size_t_vector <0>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_c <7, 8>::type, size_t_vector <7>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_c <0, 2>::type, size_t_vector <0, 1>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_c <10, 12>::type, size_t_vector <10, 11>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_c <0, 4>::type, size_t_vector <0, 1, 2, 3>>));
    BOOST_MPL_ASSERT ((std::is_same <
        count_c <17, 21>::type, size_t_vector <17, 18, 19, 20>>));

    BOOST_MPL_ASSERT ((std::is_same <
        count_c <23, 137>::type, size_t_vector <
        23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
        50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
        70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
        90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
        110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
        120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        130, 131, 132, 133, 134, 135, 136>>));
}

BOOST_AUTO_TEST_CASE (test_meta_count_c_big) {
    // Generating a count of this size should be possible without the compiler
    // batting an eyelid.
    meta::count_c <1543>::type v;
    (void) v;
}

// Simple example.

void check_2_3_4 (int a, int b, int c) {
    BOOST_CHECK_EQUAL (a, 2);
    BOOST_CHECK_EQUAL (b, 3);
    BOOST_CHECK_EQUAL (c, 4);
}

template <class Function, std::size_t ... Counts>
    void call_with (Function && function, meta::size_t_vector <Counts ...>)
{
    function (Counts ...);
}

BOOST_AUTO_TEST_CASE (test_meta_count_example) {
    call_with (check_2_3_4, meta::count_c <2, 5>::type());
}

// Example that extracts elements of a tuple.

void callee (double a, std::string s, long l) {
    BOOST_CHECK_EQUAL (a, 4.5);
    BOOST_CHECK_EQUAL (s, "Hello");
    BOOST_CHECK_EQUAL (l, 123);
}

template <class Function, class Tuple, std::size_t ... Counts>
    void call_with_helper (Function && function, Tuple arguments,
        meta::size_t_vector <Counts ...>)
{ return function (std::get <Counts> (arguments) ...); }

template <class Function, class Tuple>
    void call_with (Function && function, Tuple arguments)
{
    return call_with_helper (function, arguments,
        typename meta::count_c <std::tuple_size <Tuple>::value>::type());
}

BOOST_AUTO_TEST_CASE (test_meta_count_call_example) {
    std::tuple <float, char const *, int> t (4.5, "Hello", 123);
    call_with (callee, t);
}


BOOST_AUTO_TEST_SUITE_END()
