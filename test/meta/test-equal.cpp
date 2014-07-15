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

#define BOOST_TEST_MODULE test_meta_equal
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/equal.hpp"

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size_t.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE (test_meta_range) {
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT ((meta::equal <
        meta::list<>, meta::list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int>, meta::list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<>, meta::list<int> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::list<int>, meta::list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int>, meta::list<bool> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int, bool>, meta::list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int>, meta::list<int, bool> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::list<int, bool>, meta::list<int, bool> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int, bool>, meta::list<int, long> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <
        meta::list<int, bool>, meta::list<long, bool> >));

    // With direction
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::list<>, meta::list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::list<int>, meta::list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::list<>, meta::list<int> >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::list<int>, meta::list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::list<long>, meta::list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::list<int, bool>, meta::list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::list<int>, meta::list<int, bool> >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::list<int, bool>, meta::list<int, bool> >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::weird_list<>, meta::weird_list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::weird_list<int>, meta::weird_list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::weird_list<>, meta::weird_list<int> >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::weird_list<int>, meta::weird_list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::weird_list<long>, meta::weird_list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::weird_list<int, bool>, meta::weird_list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        meta::weird_list<int>, meta::weird_list<int, bool> >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::weird_list<int, bool>, meta::weird_list<int, bool> >));

    // With predicate
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>, meta::list<>, meta::list<> >));
    // Don't even execute any comparison
    BOOST_MPL_ASSERT_NOT ((meta::equal <mpl::equal_to <mpl::_, mpl::_>,
        meta::list<int>, meta::list<> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>, meta::list<>, meta::list<int> >));
    BOOST_MPL_ASSERT ((meta::equal <mpl::equal_to <mpl::_, mpl::_>,
        meta::list<mpl::int_ <3> >, meta::list<mpl::size_t <3> > >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>,
        meta::list<mpl::int_ <4> >, meta::list<mpl::int_ <5> > >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>,
        meta::weird_list<>, meta::weird_list<> >));
    // Don't even execute any comparison
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>,
        meta::weird_list<>, meta::weird_list<int> >));
    BOOST_MPL_ASSERT_NOT ((meta::equal <meta::list_direction,
        mpl::equal_to <mpl::_, mpl::_>,
        meta::weird_list<mpl::int_ <4> >, meta::weird_list<mpl::int_ <5> > >));
}

BOOST_AUTO_TEST_SUITE_END()

