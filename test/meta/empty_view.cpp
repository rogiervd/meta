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

#define BOOST_TEST_MODULE test_meta_empty_view
#include "../boost_unit_test.hpp"

#include "meta/empty_view.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_empty_view)

BOOST_AUTO_TEST_CASE (test_meta_empty_view) {
    // Specify direction.
    {
        typedef meta::empty_view <meta::list_direction> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::list_direction>));

        BOOST_MPL_ASSERT ((meta::empty <v>));
        BOOST_MPL_ASSERT ((meta::empty <meta::list_direction, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <0>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::list_direction, v>, boost::mpl::size_t <0>>));
    }
    // Don't specify direction: should be "front".
    {
        typedef meta::empty_view <> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::front>));

        BOOST_MPL_ASSERT ((meta::empty <v>));
        BOOST_MPL_ASSERT ((meta::empty <meta::front, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <0>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::front, v>, boost::mpl::size_t <0>>));
    }
}

BOOST_AUTO_TEST_SUITE_END()

