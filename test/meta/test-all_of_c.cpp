/*
Copyright 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_all_of_c
#include "../boost_unit_test.hpp"

#include "meta/all_of_c.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_all_of_c)

BOOST_AUTO_TEST_CASE (test_meta_all_of_c) {

    static_assert (meta::all_of_c<>::value, "");

    static_assert (!meta::all_of_c <false>::value, "");
    static_assert (meta::all_of_c <true>::value, "");

    static_assert (!meta::all_of_c <false, false>::value, "");
    static_assert (!meta::all_of_c <false, true>::value, "");
    static_assert (!meta::all_of_c <true, false>::value, "");
    static_assert (meta::all_of_c <true, true>::value, "");

    static_assert (!meta::all_of_c <false, false, false>::value, "");
    static_assert (!meta::all_of_c <false, false, true>::value, "");
    static_assert (!meta::all_of_c <false, true, false>::value, "");
    static_assert (!meta::all_of_c <false, true, true>::value, "");
    static_assert (!meta::all_of_c <true, false, false>::value, "");
    static_assert (!meta::all_of_c <true, false, true>::value, "");
    static_assert (!meta::all_of_c <true, true, false>::value, "");
    static_assert (meta::all_of_c <true, true, true>::value, "");

    static_assert (!meta::all_of_c <false, false, false, false>::value, "");
    static_assert (!meta::all_of_c <false, false, false, true>::value, "");
    static_assert (!meta::all_of_c <false, false, true, false>::value, "");
    static_assert (!meta::all_of_c <false, false, true, true>::value, "");
    static_assert (!meta::all_of_c <false, true, false, false>::value, "");
    static_assert (!meta::all_of_c <false, true, false, true>::value, "");
    static_assert (!meta::all_of_c <false, true, true, false>::value, "");
    static_assert (!meta::all_of_c <false, true, true, true>::value, "");
    static_assert (!meta::all_of_c <true, false, false, false>::value, "");
    static_assert (!meta::all_of_c <true, false, false, true>::value, "");
    static_assert (!meta::all_of_c <true, false, true, false>::value, "");
    static_assert (!meta::all_of_c <true, false, true, true>::value, "");
    static_assert (!meta::all_of_c <true, true, false, false>::value, "");
    static_assert (!meta::all_of_c <true, true, false, true>::value, "");
    static_assert (!meta::all_of_c <true, true, true, false>::value, "");
    static_assert (meta::all_of_c <true, true, true, true>::value, "");

    static_assert (!meta::all_of_c <
        false, false, false, false, false>::value, "");
    static_assert (!meta::all_of_c <
        false, false, false, false, true>::value, "");
    static_assert (!meta::all_of_c <
        false, false, false, true, false>::value, "");
    static_assert (!meta::all_of_c <
        false, false, false, true, true>::value, "");
    static_assert (!meta::all_of_c <
        false, false, true, false, false>::value, "");
    static_assert (!meta::all_of_c <
        false, false, true, false, true>::value, "");
    static_assert (!meta::all_of_c <
        false, false, true, true, false>::value, "");
    static_assert (!meta::all_of_c <
        false, false, true, true, true>::value, "");
    static_assert (!meta::all_of_c <
        false, true, false, false, false>::value, "");
    static_assert (!meta::all_of_c <
        false, true, false, false, true>::value, "");
    static_assert (!meta::all_of_c <
        false, true, false, true, false>::value, "");
    static_assert (!meta::all_of_c <
        false, true, false, true, true>::value, "");
    static_assert (!meta::all_of_c <
        false, true, true, false, false>::value, "");
    static_assert (!meta::all_of_c <
        false, true, true, false, true>::value, "");
    static_assert (!meta::all_of_c <
        false, true, true, true, false>::value, "");
    static_assert (!meta::all_of_c <
        false, true, true, true, true>::value, "");
    static_assert (!meta::all_of_c <
        true, false, false, false, false>::value, "");
    static_assert (!meta::all_of_c <
        true, false, false, false, true>::value, "");
    static_assert (!meta::all_of_c <
        true, false, false, true, false>::value, "");
    static_assert (!meta::all_of_c <
        true, false, false, true, true>::value, "");
    static_assert (!meta::all_of_c <
        true, false, true, false, false>::value, "");
    static_assert (!meta::all_of_c <
        true, false, true, false, true>::value, "");
    static_assert (!meta::all_of_c <
        true, false, true, true, false>::value, "");
    static_assert (!meta::all_of_c <
        true, false, true, true, true>::value, "");
    static_assert (!meta::all_of_c <
        true, true, false, false, false>::value, "");
    static_assert (!meta::all_of_c <
        true, true, false, false, true>::value, "");
    static_assert (!meta::all_of_c <
        true, true, false, true, false>::value, "");
    static_assert (!meta::all_of_c <
        true, true, false, true, true>::value, "");
    static_assert (!meta::all_of_c <
        true, true, true, false, false>::value, "");
    static_assert (!meta::all_of_c <
        true, true, true, false, true>::value, "");
    static_assert (!meta::all_of_c <
        true, true, true, true, false>::value, "");
    static_assert (meta::all_of_c <
        true, true, true, true, true>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
