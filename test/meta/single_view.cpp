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

#define BOOST_TEST_MODULE test_meta_single_view
#include "../boost_unit_test.hpp"

#include "meta/single_view.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_single_view)

BOOST_AUTO_TEST_CASE (test_meta_single_view) {
    // Specify direction.
    {
        typedef meta::single_view <meta::list_direction, int> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::list_direction>));

        BOOST_MPL_ASSERT_NOT ((meta::empty <v>));
        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::list_direction, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <1>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::list_direction, v>, boost::mpl::size_t <1>>));

        BOOST_MPL_ASSERT ((std::is_same <meta::first <v>::type, int>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::list_direction, v>::type, int>));

        // The result of drop <single_view <...> is not defined to be an
        // empty_view.
        // But then, if the following passes, then it is left to empty_view.cpp
        // to test its behaviour.
        BOOST_MPL_ASSERT ((std::is_same <
            meta::drop <v>::type, meta::empty_view <meta::list_direction>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::drop <meta::list_direction, v>::type,
                meta::empty_view <meta::list_direction>>));
    }
    // Don't specify direction: should be "front".
    {
        typedef meta::single_view <bool> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::front>));

        BOOST_MPL_ASSERT_NOT ((meta::empty <v>));
        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::front, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <1>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::front, v>, boost::mpl::size_t <1>>));

        BOOST_MPL_ASSERT ((std::is_same <meta::first <v>::type, bool>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::front, v>::type, bool>));

        BOOST_MPL_ASSERT ((std::is_same <
            meta::drop <v>::type, meta::empty_view <meta::front>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::drop <meta::front, v>::type,
                meta::empty_view <meta::front>>));
    }
}

BOOST_AUTO_TEST_SUITE_END()

