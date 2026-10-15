// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_flatten
#include <boost/test/unit_test.hpp>

#include <type_traits>

#include "list.hpp"
#include "meta/flatten.hpp"

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_flatten)

// \todo weird_list?
BOOST_AUTO_TEST_CASE(test_meta_flatten)
{
    using meta::list;
    using std::is_same;

    BOOST_MPL_ASSERT((is_same<meta::flatten<list<>>::type, meta::list<>>) );
    BOOST_MPL_ASSERT(
        (is_same<meta::flatten<list<list<>>>::type, meta::list<>>) );
    BOOST_MPL_ASSERT(
        (is_same<meta::flatten<list<list<>, list<>>>::type, meta::list<>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::flatten<list<list<int>, list<>>>::type, meta::list<int>>) );
    BOOST_MPL_ASSERT(
        (is_same<
            meta::flatten<list<list<>, list<int>>>::type, meta::list<int>>) );
    BOOST_MPL_ASSERT((is_same<
                      meta::flatten<list<list<bool>, list<int>>>::type,
                      meta::list<bool, int>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::flatten<
                list<list<>, list<int>, list<float, bool>, list<double>>>::type,
            meta::list<int, float, bool, double>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::flatten<
                list<list<int, float>, list<>, list<bool>, list<double>>>::type,
            meta::list<int, float, bool, double>>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::flatten<list<
                          list<int, float>, list<bool>, list<bool, float>,
                          list<double>>>::type,
                      meta::list<int, float, bool, bool, float, double>>) );
}

BOOST_AUTO_TEST_SUITE_END()
