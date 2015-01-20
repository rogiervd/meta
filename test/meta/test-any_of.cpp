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

#define BOOST_TEST_MODULE test_meta_any
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/any_of.hpp"

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_any_of)

BOOST_AUTO_TEST_CASE (test_meta_any_of) {
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT_NOT ((meta::any_of <meta::list<>>));

    BOOST_MPL_ASSERT_NOT ((meta::any_of <meta::list <mpl::false_>>));
    BOOST_MPL_ASSERT ((meta::any_of <meta::list <mpl::true_>>));

    BOOST_MPL_ASSERT_NOT ((meta::any_of <
        meta::list <mpl::false_, mpl::false_>>));
    BOOST_MPL_ASSERT ((meta::any_of <meta::list <mpl::false_, mpl::true_>>));
    BOOST_MPL_ASSERT ((meta::any_of <meta::list <mpl::true_, mpl::false_>>));
    BOOST_MPL_ASSERT ((meta::any_of <meta::list <mpl::true_, mpl::true_>>));

    // weird_list
    BOOST_MPL_ASSERT_NOT ((
        meta::any_of <meta::list_direction, meta::weird_list<>>));

    BOOST_MPL_ASSERT_NOT ((meta::any_of <
        meta::list_direction, meta::weird_list <mpl::false_, mpl::false_>>));
    BOOST_MPL_ASSERT ((meta::any_of <
        meta::list_direction, meta::weird_list <mpl::false_, mpl::true_>>));
    BOOST_MPL_ASSERT ((meta::any_of <
        meta::list_direction, meta::weird_list <mpl::true_, mpl::false_>>));
    BOOST_MPL_ASSERT ((meta::any_of <
        meta::list_direction, meta::weird_list <mpl::true_, mpl::true_>>));
}

BOOST_AUTO_TEST_SUITE_END()
