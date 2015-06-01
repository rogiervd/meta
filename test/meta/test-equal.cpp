/*
Copyright 2011, 2012 Rogier van Dalen.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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

