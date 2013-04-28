/*
Copyright 2011, 2012 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_transform
#include "../boost_unit_test.hpp"

#include "meta/transform.hpp"

#include <type_traits>
#include "list.hpp"

template <typename Type> struct type_wrapper {};

#include <boost/mpl/placeholders.hpp>

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE (test_meta_transform) {
    using boost::mpl::_1;
    using std::is_same;

    BOOST_MPL_ASSERT ((is_same <
        meta::transform <type_wrapper <_1>, meta::list<> >::type,
        meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::transform <meta::list_direction, type_wrapper <_1>, meta::list<>
            >::type,
        meta::list<> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::transform <type_wrapper <_1>,
            meta::list <int, long, bool> >::type,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
    BOOST_MPL_ASSERT ((is_same <
        meta::transform <meta::list_direction, type_wrapper <_1>,
            meta::list <int, long, bool> >::type,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::transform <meta::list_direction, type_wrapper <_1>,
            meta::weird_list <int, long, bool> >::type,
        meta::weird_list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
}

BOOST_AUTO_TEST_SUITE_END()

