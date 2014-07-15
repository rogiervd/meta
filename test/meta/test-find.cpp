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

#define BOOST_TEST_MODULE test_meta_find
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/find.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE (test_meta_find) {
    using std::is_same;
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_floating_point <mpl::_>, meta::list<> >::type,
        meta::list<>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_floating_point <mpl::_>, list4>::type,
        meta::list <float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_pod <mpl::_>, list4>::type,
        list4
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_unsigned <mpl::_>, list4>::type,
        meta::list<bool, float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_class <mpl::_>, list4>::type,
        meta::list<>
        >));


    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_floating_point <mpl::_>, meta::weird_list<> >::type,
        meta::weird_list<>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_pod <mpl::_>, weird_list4>::type,
        weird_list4
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_unsigned <mpl::_>, weird_list4>::type,
        meta::weird_list<bool, float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_class <mpl::_>, weird_list4>::type,
        meta::weird_list<>
        >));
}

BOOST_AUTO_TEST_SUITE_END()

