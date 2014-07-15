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

#define BOOST_TEST_MODULE test_meta_flatten
#include "../boost_unit_test.hpp"

#include <type_traits>

#include "list.hpp"
#include "meta/flatten.hpp"
#include "meta/mpl.hpp"

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_flatten)

// \todo weird_list?
BOOST_AUTO_TEST_CASE (test_meta_flatten) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using meta::list;

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <> >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<> > >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<>, list<> > >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list <int>, list<> > >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<>, list <int> > >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list <bool>, list <int> > >::type,
        meta::list <bool, int> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<>, list <int>, list <float, bool>, list <double> >
            >::type,
        meta::list <int, float, bool, double> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<int, float>, list <>, list <bool>, list <double> >
            >::type,
        meta::list <int, float, bool, double> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<int, float>, list <bool>, list <bool, float>,
                list <double> >
            >::type,
        meta::list <int, float, bool, bool, float, double> >));
}

BOOST_AUTO_TEST_SUITE_END()

