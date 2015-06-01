/*
Copyright 2013 Rogier van Dalen.

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
