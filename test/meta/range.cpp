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

#define BOOST_TEST_MODULE test_meta_range
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/range.hpp"

typedef meta::list <> list0;
typedef meta::list <int> list1;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int> weird_list1;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/placeholders.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE (test_meta_range) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using mpl::equal_to;
    typedef meta::list_direction dir;

    using meta::empty;
    using meta::size;
    using meta::first;
    using meta::drop;
    using meta::push;

    BOOST_MPL_ASSERT ((meta::is_range <list0>));
    BOOST_MPL_ASSERT ((meta::is_range <list1>));
    BOOST_MPL_ASSERT ((meta::is_range <list4>));
    BOOST_MPL_ASSERT_NOT ((meta::is_range <int>));
    BOOST_MPL_ASSERT_NOT ((meta::is_range <bool>));

    // empty
    BOOST_MPL_ASSERT ((empty <list0>));
    BOOST_MPL_ASSERT_NOT ((empty <list1>));
    BOOST_MPL_ASSERT_NOT ((empty <list4>));

    BOOST_MPL_ASSERT ((empty <dir, list0>));
    BOOST_MPL_ASSERT_NOT ((empty <dir, list1>));
    BOOST_MPL_ASSERT_NOT ((empty <dir, list4>));

    BOOST_MPL_ASSERT ((empty <dir, weird_list0>));
    BOOST_MPL_ASSERT_NOT ((empty <dir, weird_list1>));
    BOOST_MPL_ASSERT_NOT ((empty <dir, weird_list4>));

    // size
    BOOST_MPL_ASSERT ((equal_to <size <list0>, mpl::size_t <0> >));
    BOOST_MPL_ASSERT ((equal_to <size <list1>, mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <size <list4>, mpl::size_t <4> >));

    BOOST_MPL_ASSERT ((equal_to <size <dir, list0>, mpl::size_t <0> >));
    BOOST_MPL_ASSERT ((equal_to <size <dir, list1>, mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <size <dir, list4>, mpl::size_t <4> >));

    BOOST_MPL_ASSERT ((equal_to <size <dir, weird_list0>, mpl::size_t <0> >));
    BOOST_MPL_ASSERT ((equal_to <size <dir, weird_list1>, mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <size <dir, weird_list4>, mpl::size_t <4> >));

    // first
    BOOST_MPL_ASSERT ((is_same <first <list1>::type, int>));
    BOOST_MPL_ASSERT ((is_same <first <list4>::type, int>));

    BOOST_MPL_ASSERT ((is_same <first <dir, list1>::type, int>));
    BOOST_MPL_ASSERT ((is_same <first <dir, list4>::type, int>));

    BOOST_MPL_ASSERT ((is_same <first <dir, weird_list1>::type, int>));
    BOOST_MPL_ASSERT ((is_same <first <dir, weird_list4>::type, int>));

    // drop one
    BOOST_MPL_ASSERT ((is_same <drop <list1>::type, meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <drop <list4>::type,
        meta::list <bool, float, double> >));

    BOOST_MPL_ASSERT ((is_same <drop <dir, list1>::type, meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <drop <dir, list4>::type,
        meta::list <bool, float, double> >));

    BOOST_MPL_ASSERT ((is_same <drop <dir, weird_list1>::type,
        meta::weird_list<> >));
    BOOST_MPL_ASSERT ((is_same <drop <dir, weird_list4>::type,
        meta::weird_list <bool, float, double> >));

    // drop
    BOOST_MPL_ASSERT ((is_same <drop <mpl::size_t <2>, list4>::type,
        meta::list <float, double> >));
    BOOST_MPL_ASSERT ((is_same <drop <mpl::int_ <4>, list4>::type,
        meta::list <> >));

    BOOST_MPL_ASSERT ((is_same <drop <dir, mpl::size_t <2>, list4>::type,
        meta::list <float, double> >));
    BOOST_MPL_ASSERT ((is_same <drop <dir, mpl::int_ <4>, list4>::type,
        meta::list <> >));

    BOOST_MPL_ASSERT ((is_same <drop <dir, mpl::size_t <2>, weird_list4>::type,
        meta::weird_list <float, double> >));
    BOOST_MPL_ASSERT ((is_same <drop <dir, mpl::int_ <4>, weird_list4>::type,
        meta::weird_list <> >));

    // push
    BOOST_MPL_ASSERT ((is_same <push <long, list0>::type,
        meta::list <long> >));
    BOOST_MPL_ASSERT ((is_same <push <long, list1>::type,
        meta::list <long, int> >));
    BOOST_MPL_ASSERT ((is_same <push <long, list4>::type,
        meta::list <long, int, bool, float, double> >));

    BOOST_MPL_ASSERT ((is_same <push <dir, long, list0>::type,
        meta::list <long> >));
    BOOST_MPL_ASSERT ((is_same <push <dir, long, list1>::type,
        meta::list <long, int> >));
    BOOST_MPL_ASSERT ((is_same <push <dir, long, list4>::type,
        meta::list <long, int, bool, float, double> >));

    BOOST_MPL_ASSERT ((is_same <push <dir, long, weird_list0>::type,
        meta::weird_list <long> >));
    BOOST_MPL_ASSERT ((is_same <push <dir, long, weird_list1>::type,
        meta::weird_list <long, int> >));
    BOOST_MPL_ASSERT ((is_same <push <dir, long, weird_list4>::type,
        meta::weird_list <long, int, bool, float, double> >));
}

BOOST_AUTO_TEST_SUITE_END()

