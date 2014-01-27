/*
Copyright 2011, 2012, 2014 Rogier van Dalen.

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
#include "list.hpp"

template <typename Type> struct type_wrapper {};

#include <boost/mpl/placeholders.hpp>
#include "meta/equal.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_transform)

BOOST_AUTO_TEST_CASE (test_meta_transform) {
    using boost::mpl::_;

    BOOST_MPL_ASSERT ((meta::equal <
        meta::transform <type_wrapper <_>, meta::list<> >,
        meta::list<>
        >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>, meta::list<> >,
        meta::list<>
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::transform <type_wrapper <_>,
            meta::list <int, long, bool> >,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>,
            meta::list <int, long, bool> >,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>,
            meta::weird_list <int, long, bool> >,
        meta::weird_list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
}

BOOST_AUTO_TEST_SUITE_END()

