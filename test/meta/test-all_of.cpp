/*
Copyright 2013, 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_all
#include "../boost_unit_test.hpp"

#include "meta/all_of.hpp"

#include <boost/mpl/bool.hpp>
#include "list.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_all_of)

BOOST_AUTO_TEST_CASE (test_meta_all_of) {
    static_assert (meta::all_of <meta::list<>>::value, "");

    static_assert (!meta::all_of <meta::list <mpl::false_>>::value, "");
    static_assert (meta::all_of <meta::list <mpl::true_>>::value, "");

    static_assert (!meta::all_of <
        meta::list <mpl::false_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <
        meta::list <mpl::false_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <
        meta::list <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::all_of <
        meta::list <mpl::true_, mpl::true_>>::value, "");

    // Short-circuit.
    static_assert (!meta::all_of <meta::list <mpl::false_, int>>::value, "");
    static_assert (!meta::all_of <
        meta::list <mpl::false_, int, bool>>::value, "");

    // weird_list
    static_assert (meta::all_of <meta::list_direction,
        meta::weird_list<>>::value, "");

    static_assert (!meta::all_of <meta::list_direction,
        meta::weird_list <mpl::false_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <meta::list_direction,
        meta::weird_list <mpl::false_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <meta::list_direction,
        meta::weird_list <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::all_of <meta::list_direction,
        meta::weird_list <mpl::true_, mpl::true_>>::value, "");
}

// Without including meta/vector.hpp!
// This should just use the type.
BOOST_AUTO_TEST_CASE (test_meta_all_of_vector) {
    static_assert (meta::all_of <meta::vector<>>::value, "");

    static_assert (!meta::all_of <meta::vector <mpl::false_>>::value, "");
    static_assert (meta::all_of <meta::vector <mpl::true_>>::value, "");

    static_assert (!meta::all_of <
        meta::vector <mpl::false_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <
        meta::vector <mpl::false_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <
        meta::vector <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::all_of <
        meta::vector <mpl::true_, mpl::true_>>::value, "");

    static_assert (!meta::all_of <meta::vector <
        mpl::false_, mpl::false_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::false_, mpl::false_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::false_, mpl::true_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::false_, mpl::true_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::true_, mpl::false_, mpl::false_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::true_, mpl::false_, mpl::true_>>::value, "");
    static_assert (!meta::all_of <meta::vector <
        mpl::true_, mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::all_of <meta::vector <
        mpl::true_, mpl::true_, mpl::true_>>::value, "");

    // Short-circuit.
    static_assert (!meta::all_of <
        meta::vector <mpl::false_, int>>::value, "");
    static_assert (!meta::all_of <
        meta::vector <mpl::false_, int, bool>>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
