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

#define BOOST_TEST_MODULE test_meta_scan
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/scan.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_scan)

BOOST_AUTO_TEST_CASE (test_meta_scan) {
    using std::is_same;
    using boost::mpl::equal_to;
    namespace mpl = boost::mpl;

    typedef meta::scan <meta::push <mpl::_2, mpl::_1>,
        void, list0> list_void;
    typedef meta::scan <meta::push <mpl::_2, mpl::_1>,
        meta::list<>, list4> list_list;

    // list_void.
    BOOST_MPL_ASSERT_NOT ((meta::empty <list_void>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <list_void>, boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((is_same <meta::first <list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <list_void>::type>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <list_void>::type>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <list_void>::type>, boost::mpl::size_t <0>>));

    // list_list.
    BOOST_MPL_ASSERT_NOT ((meta::empty <list_list>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <list_list>, boost::mpl::size_t <5>>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <list_list>::type,
        meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <list_list>::type>::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, list_list>::type>::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, list_list>::type>::type,
        meta::list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, list_list>::type>::type,
        meta::list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, list_list>::type>));

    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <mpl::size_t <4>, list_list>::type>,
        boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <mpl::size_t <5>, list_list>::type>,
        boost::mpl::size_t <0>>));

    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        void, list0> dir_list_void;
    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        meta::list<>, list4> dir_list_list;

    BOOST_MPL_ASSERT ((is_same <meta::first <dir_list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <dir_list_void>::type>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <dir_list_list>::type,
        meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <dir_list_list>::type>::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, dir_list_list>::type>::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, dir_list_list>::type>::type,
        meta::list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, dir_list_list>::type>::type,
        meta::list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, dir_list_list>::type>));

    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        void, weird_list0> weird_list_void;
    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        meta::weird_list<>, weird_list4> weird_list_list;

    BOOST_MPL_ASSERT ((is_same <meta::first <weird_list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <weird_list_void>::type>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <weird_list_list>::type,
        meta::weird_list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <weird_list_list>::type>::type,
        meta::weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, weird_list_list>::type>::type,
        meta::weird_list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, weird_list_list>::type>::type,
        meta::weird_list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, weird_list_list>::type>::type,
        meta::weird_list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, weird_list_list>::type>));
}

BOOST_AUTO_TEST_SUITE_END()

