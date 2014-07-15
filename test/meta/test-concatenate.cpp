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

#define BOOST_TEST_MODULE test_meta_concatenate
#include "../boost_unit_test.hpp"

#include <type_traits>
#include "list.hpp"
#include "meta/concatenate.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_concatenate)

BOOST_AUTO_TEST_CASE (test_meta_concatenate) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using meta::list;
    using meta::weird_list;
    typedef meta::list_direction direction;

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list<>, list<> >::type,
        list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list<> >::type,
        list<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list<>, list <int> >::type,
        list<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list <bool> >::type,
        list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int, float>, list <bool> >::type,
        list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list <bool, float> >::type,
        list <int, bool, float> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int>, list<> >::type,
        list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list<>, list <int> >::type,
        list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int>, list <bool> >::type,
        list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int, float>, list <bool> >::type,
        list <int, float, bool> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int>, weird_list<> >::type,
        weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list<>, weird_list <int> >::type,
        weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int>, weird_list <bool>
            >::type,
        weird_list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int, float>, weird_list <bool>
            >::type,
        weird_list <int, float, bool> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <weird_list <int, float>, list <bool> >::type,
        list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int, float>, weird_list <bool>
            >::type,
        weird_list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int, float>, list <bool>
            >::type,
        list <int, float, bool> >));
}

BOOST_AUTO_TEST_SUITE_END()

