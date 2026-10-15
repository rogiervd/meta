// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_concatenate
#include <boost/test/unit_test.hpp>

#include <type_traits>
#include "list.hpp"

#include <boost/mpl/assert.hpp>
#include "meta/concatenate.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_concatenate)

BOOST_AUTO_TEST_CASE(test_meta_concatenate)
{
    using meta::list;
    using meta::weird_list;
    using std::is_same;
    typedef meta::list_direction direction;

    BOOST_MPL_ASSERT(
        (is_same<meta::concatenate<list<>, list<>>::type, list<>>) );
    BOOST_MPL_ASSERT(
        (is_same<meta::concatenate<list<int>, list<>>::type, list<int>>) );
    BOOST_MPL_ASSERT(
        (is_same<meta::concatenate<list<>, list<int>>::type, list<int>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<list<int>, list<bool>>::type, list<int, bool>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<list<int, float>, list<bool>>::type,
                      list<int, float, bool>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<list<int>, list<bool, float>>::type,
                      list<int, bool, float>>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<direction, list<int>, list<>>::type,
                      list<int>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<direction, list<>, list<int>>::type,
                      list<int>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<direction, list<int>, list<bool>>::type,
                      list<int, bool>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<direction, list<int, float>, list<bool>>::type,
            list<int, float, bool>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<direction, weird_list<int>, weird_list<>>::type,
            weird_list<int>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<direction, weird_list<>, weird_list<int>>::type,
            weird_list<int>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<
                          direction, weird_list<int>, weird_list<bool>>::type,
                      weird_list<int, bool>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<
                direction, weird_list<int, float>, weird_list<bool>>::type,
            weird_list<int, float, bool>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::concatenate<weird_list<int, float>, list<bool>>::type,
            list<int, float, bool>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<
                          direction, list<int, float>, weird_list<bool>>::type,
                      weird_list<int, float, bool>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::concatenate<
                          direction, weird_list<int, float>, list<bool>>::type,
                      list<int, float, bool>>) );
}

BOOST_AUTO_TEST_SUITE_END()
