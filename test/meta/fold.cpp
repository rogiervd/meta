/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

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

#define BOOST_TEST_MODULE test_meta_range
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/fold.hpp"
#include "meta/fold_reverse.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/placeholders.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_fold)

BOOST_AUTO_TEST_CASE (test_meta_fold) {
    namespace mpl = boost::mpl;
    using std::is_same;

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <mpl::plus <mpl::_1, mpl::_2>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <mpl::plus <mpl::_1, mpl::_2>, mpl::int_ <7>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>, mpl::int_ <7>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <mpl::divides <mpl::_1, mpl::_2>, mpl::int_ <280>,
            meta::list <mpl::int_ <2>, mpl::int_ <7>, mpl::int_ <-4> >
        >::type,
        mpl::int_ <-5> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::list<>,
            meta::list <int, bool>
        >::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::list_direction, meta::push <mpl::_2, mpl::_1>, meta::list<>,
            meta::list <int, bool>
        >::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::list<>,
            meta::list <>
        >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::list<int>,
            meta::list <>
        >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::list<int>,
            meta::list <bool>
        >::type,
        meta::list <bool, int> >));

    // weird_list
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>,
            meta::weird_list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>,
            mpl::int_ <7>,
            meta::weird_list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::fold <meta::list_direction,
            meta::push <meta::list_direction, mpl::_2, mpl::_1>,
            meta::weird_list<>,
            meta::weird_list <int, bool>
        >::type,
        meta::weird_list <bool, int> >));
}

BOOST_AUTO_TEST_CASE (test_meta_fold_reverse) {
    namespace mpl = boost::mpl;
    using boost::is_same;

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <mpl::plus <mpl::_1, mpl::_2>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <mpl::plus <mpl::_1, mpl::_2>, mpl::int_ <7>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>, mpl::int_ <7>,
            meta::list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <mpl::divides <mpl::_1, mpl::_2>, mpl::int_ <2>,
            meta::list <mpl::int_ <-4> >
        >::type,
        mpl::int_ <-2> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <mpl::divides <mpl::_1, mpl::_2>, mpl::int_ <2>,
            meta::list <mpl::int_ <8>, mpl::int_ <12>, mpl::int_ <24>, mpl::int_ <-4> >
        >::type,
        mpl::int_ <-8> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <mpl::divides <mpl::_1, mpl::_2>,
            meta::list <mpl::int_ <8>, mpl::int_ <12>, mpl::int_ <24>, mpl::int_ <-2> >
        >::type,
        mpl::int_ <-8> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::fold_reverse <meta::push <mpl::_1, mpl::_2>, meta::list<>,
            meta::list <int, bool>
        >::type,
        meta::list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold_reverse <meta::push <mpl::_1, mpl::_2>, meta::list<>,
            meta::list <>
        >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold_reverse <meta::push <mpl::_1, mpl::_2>, meta::list<int>,
            meta::list <>
        >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::fold_reverse <meta::push <mpl::_1, mpl::_2>, meta::list<int>,
            meta::list <bool>
        >::type,
        meta::list <bool, int> >));

    // weird_list
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <meta::list_direction, mpl::plus <mpl::_1, mpl::_2>,
            meta::weird_list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <5> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::fold_reverse <meta::list_direction,
            mpl::plus <mpl::_1, mpl::_2>,
            mpl::int_ <7>,
            meta::weird_list <mpl::int_ <4>, mpl::int_ <2>, mpl::int_ <-1> >
        >::type,
        mpl::int_ <12> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::fold_reverse <meta::list_direction,
            meta::push <meta::list_direction, mpl::_1, mpl::_2>,
            meta::weird_list <int>,
            meta::weird_list <bool>
        >::type,
        meta::weird_list <bool, int> >));
}

BOOST_AUTO_TEST_SUITE_END()

