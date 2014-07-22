/*
Copyright 2013 Rogier van Dalen.

This file is part of Rogier van Dalen's Meta-programming library for C++.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BOOST_TEST_MODULE test_meta_count
#include "../boost_unit_test.hpp"

#include "meta/count.hpp"

#include <type_traits>
#include <tuple>
#include <string>

#include <boost/mpl/assert.hpp>

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_count)

BOOST_AUTO_TEST_CASE (test_meta_count) {
    // Without start.
    BOOST_MPL_ASSERT ((std::is_same <meta::count <0>::type, meta::vector<>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <1>::type, meta::vector<
        std::integral_constant <std::size_t, 0>>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <2>::type, meta::vector<
        std::integral_constant <std::size_t, 0>,
        std::integral_constant <std::size_t, 1>>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <4>::type, meta::vector<
        std::integral_constant <std::size_t, 0>,
        std::integral_constant <std::size_t, 1>,
        std::integral_constant <std::size_t, 2>,
        std::integral_constant <std::size_t, 3>>>));

    // With start.
    BOOST_MPL_ASSERT ((std::is_same <meta::count <0, 0>::type, meta::vector<
        >>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <3, 3>::type, meta::vector<
        >>));

    BOOST_MPL_ASSERT ((std::is_same <meta::count <0, 1>::type, meta::vector<
        std::integral_constant <std::size_t, 0>>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <7, 8>::type, meta::vector<
        std::integral_constant <std::size_t, 7>>>));

    BOOST_MPL_ASSERT ((std::is_same <meta::count <0, 2>::type, meta::vector<
        std::integral_constant <std::size_t, 0>,
        std::integral_constant <std::size_t, 1>>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <10, 12>::type, meta::vector<
        std::integral_constant <std::size_t, 10>,
        std::integral_constant <std::size_t, 11>>>));

    BOOST_MPL_ASSERT ((std::is_same <meta::count <0, 4>::type, meta::vector<
        std::integral_constant <std::size_t, 0>,
        std::integral_constant <std::size_t, 1>,
        std::integral_constant <std::size_t, 2>,
        std::integral_constant <std::size_t, 3>>>));
    BOOST_MPL_ASSERT ((std::is_same <meta::count <17, 21>::type, meta::vector<
        std::integral_constant <std::size_t, 17>,
        std::integral_constant <std::size_t, 18>,
        std::integral_constant <std::size_t, 19>,
        std::integral_constant <std::size_t, 20>>>));
}

// Simple example.

void check_2_3_4 (int a, int b, int c) {
    BOOST_CHECK_EQUAL (a, 2);
    BOOST_CHECK_EQUAL (b, 3);
    BOOST_CHECK_EQUAL (c, 4);
}

template <class Function, class ... Counts>
    void call_with (Function && function, meta::vector <Counts ...>)
{
    function (Counts::value ...);
}

BOOST_AUTO_TEST_CASE (test_meta_count_example) {
    call_with (check_2_3_4, meta::count <2, 5>::type());
}

// Example that extracts elements of a tuple.

void callee (double a, std::string s, long l) {
    BOOST_CHECK_EQUAL (a, 4.5);
    BOOST_CHECK_EQUAL (s, "Hello");
    BOOST_CHECK_EQUAL (l, 123);
}

template <class Function, class Tuple, class ... Counts>
    void call_with_helper (Function && function, Tuple arguments,
        meta::vector <Counts ...>)
{ return function (std::get <Counts::value> (arguments) ...); }

template <class Function, class Tuple>
    void call_with (Function && function, Tuple arguments)
{
    return call_with_helper (function, arguments,
        typename meta::count <std::tuple_size <Tuple>::value>::type());
}

BOOST_AUTO_TEST_CASE (test_meta_count_call_example) {
    std::tuple <float, char const *, int> t (4.5, "Hello", 123);
    call_with (callee, t);
}

BOOST_AUTO_TEST_SUITE_END()
