// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_contains
#include <boost/test/unit_test.hpp>

#include "list.hpp"
#include "meta/contains.hpp"

typedef meta::list<> list0;
typedef meta::list<int, bool, float, double> list4;

typedef meta::weird_list<> weird_list0;
typedef meta::weird_list<int, bool, float, double> weird_list4;

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_contains)

BOOST_AUTO_TEST_CASE(test_meta_contains)
{
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT_NOT((meta::contains<int, meta::list<>>) );

    BOOST_MPL_ASSERT_NOT((meta::contains<int, meta::list<float, double>>) );
    BOOST_MPL_ASSERT_NOT((meta::contains<void, meta::list<float, double>>) );
    BOOST_MPL_ASSERT((meta::contains<float, meta::list<float, double>>) );
    BOOST_MPL_ASSERT((meta::contains<double, meta::list<float, double>>) );

    BOOST_MPL_ASSERT((meta::contains<int, list4>) );
    BOOST_MPL_ASSERT((meta::contains<bool, list4>) );
    BOOST_MPL_ASSERT((meta::contains<double, list4>) );

    BOOST_MPL_ASSERT_NOT(
        (meta::contains<meta::list_direction, int, meta::weird_list<>>) );

    BOOST_MPL_ASSERT_NOT(
        (meta::contains<
            meta::list_direction, int, meta::weird_list<float, double>>) );
    BOOST_MPL_ASSERT_NOT(
        (meta::contains<
            meta::list_direction, void, meta::weird_list<float, double>>) );
    BOOST_MPL_ASSERT(
        (meta::contains<
            meta::list_direction, float, meta::weird_list<float, double>>) );
    BOOST_MPL_ASSERT(
        (meta::contains<
            meta::list_direction, double, meta::weird_list<float, double>>) );

    BOOST_MPL_ASSERT((meta::contains<meta::list_direction, int, weird_list4>) );
    BOOST_MPL_ASSERT(
        (meta::contains<meta::list_direction, bool, weird_list4>) );
    BOOST_MPL_ASSERT(
        (meta::contains<meta::list_direction, double, weird_list4>) );
}

BOOST_AUTO_TEST_SUITE_END()
