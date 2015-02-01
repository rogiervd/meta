/*
Copyright 2014, 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE set
#include "../boost_unit_test.hpp"

#include "meta/set.hpp"
#include "meta/range.hpp"

#include <boost/mpl/equal.hpp>
#include "meta/vector.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_set)

typedef meta::set <> set_0;
typedef meta::set <int> set_1;
typedef meta::set <bool, int> set_2;

BOOST_AUTO_TEST_CASE (test_meta_set) {
    // empty.
    BOOST_MPL_ASSERT ((meta::empty <set_0>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <set_1>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <set_2>));

    // size.
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <set_0>, boost::mpl::size_t <0>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <set_1>, boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <set_2>, boost::mpl::size_t <2>>));

    // first.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::first <set_1>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::first <set_2>::type, bool>));

    // drop.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::drop <set_1>::type, set_0>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::drop <set_2>::type, set_1>));

    // push.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::push <int, set_0>::type, set_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::push <bool, set_1>::type, set_2>));

    // contains.
    BOOST_MPL_ASSERT_NOT ((meta::contains <int, set_0>));
    BOOST_MPL_ASSERT_NOT ((meta::contains <bool, set_0>));
    BOOST_MPL_ASSERT_NOT ((meta::contains <long, set_0>));

    BOOST_MPL_ASSERT ((meta::contains <int, set_1>));
    BOOST_MPL_ASSERT_NOT ((meta::contains <bool, set_1>));
    BOOST_MPL_ASSERT_NOT ((meta::contains <long, set_1>));

    BOOST_MPL_ASSERT ((meta::contains <int, set_2>));
    BOOST_MPL_ASSERT ((meta::contains <bool, set_2>));
    BOOST_MPL_ASSERT_NOT ((meta::contains <long, set_2>));

    // has_key: the same as contains.
    BOOST_MPL_ASSERT_NOT ((meta::has_key <int, set_0>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <bool, set_0>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, set_0>));

    BOOST_MPL_ASSERT ((meta::has_key <int, set_1>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <bool, set_1>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, set_1>));

    BOOST_MPL_ASSERT ((meta::has_key <int, set_2>));
    BOOST_MPL_ASSERT ((meta::has_key <bool, set_2>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, set_2>));

    // insert: new element.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <int, set_0>::type, set_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <bool, set_1>::type, set_2>));
    // Existing element.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <int, set_1>::type, set_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <int, set_2>::type, set_2>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <bool, set_2>::type, set_2>));

    // remove.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::remove <int, set_1>::type, set_0>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::remove <bool, set_2>::type, set_1>));
}

BOOST_AUTO_TEST_CASE (test_meta_as_set) {
    /*{
        // Causes an error because a set cannot contain the same element twice.
        typedef meta::set <int, long, int> s;
        typename meta::contains <int, s>::type l;
    }*/
    {
        BOOST_MPL_ASSERT ((std::is_same <
            typename meta::as_set <meta::vector <>>::type,
            meta::set<>>));
        BOOST_MPL_ASSERT ((std::is_same <
            typename meta::as_set <meta::vector <int>>::type,
            meta::set <int>>));
        BOOST_MPL_ASSERT ((std::is_same <
            typename meta::as_set <meta::vector <int, bool>>::type,
            meta::set <int, bool>>));

        // Duplicate elements are represented only once.
        BOOST_MPL_ASSERT ((std::is_same <
            typename meta::as_set <meta::vector <int, bool, int>>::type,
            meta::set <bool, int>>));
        BOOST_MPL_ASSERT ((std::is_same <
            typename meta::as_set <meta::vector <int, int, bool, int>>::type,
            meta::set <bool, int>>));
    }
}

BOOST_AUTO_TEST_CASE (test_meta_is_subset) {
    static_assert (meta::is_subset <meta::set<>, meta::set<>>::value, "");
    static_assert (!meta::is_subset <meta::set <int>, meta::set<>>::value, "");
    static_assert (meta::is_subset <meta::set<>, meta::set <int>>::value, "");
    static_assert (meta::is_subset <meta::set <int>,
        meta::set <int>>::value, "");

    static_assert (meta::is_subset <meta::set<>,
        meta::set <bool>>::value, "");
    static_assert (!meta::is_subset <meta::set <int>,
        meta::set <bool>>::value, "");
    static_assert (meta::is_subset <meta::set<>,
        meta::set <int, bool>>::value, "");
    static_assert (meta::is_subset <meta::set <int>,
        meta::set <bool, int>>::value, "");

    static_assert (meta::is_subset <meta::set <bool>,
        meta::set <bool>>::value, "");
    static_assert (!meta::is_subset <meta::set <int, bool>,
        meta::set <bool>>::value, "");
    static_assert (meta::is_subset <meta::set <bool>,
        meta::set <int, bool>>::value, "");
    static_assert (meta::is_subset <meta::set <int, bool>,
        meta::set <bool, int>>::value, "");

    static_assert (meta::is_subset <meta::set <bool, float>,
        meta::set <bool, float>>::value, "");
    static_assert (!meta::is_subset <meta::set <int, bool, float>,
        meta::set <float, bool>>::value, "");
    static_assert (meta::is_subset <meta::set <bool, float>,
        meta::set <int, float, bool>>::value, "");
    static_assert (meta::is_subset <meta::set <int, float, bool>,
        meta::set <bool, float, int>>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
