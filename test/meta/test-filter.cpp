// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_range
#include <boost/test/unit_test.hpp>

#include "list.hpp"
#include "meta/filter.hpp"

typedef meta::list<> list0;
typedef meta::list<int, bool, float, double> list4;

typedef meta::weird_list<> weird_list0;
typedef meta::weird_list<int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "meta/equal.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_filter)

BOOST_AUTO_TEST_CASE(test_meta_filter)
{
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::filter<std::is_floating_point<mpl::_>, meta::list<>>,
            meta::list<>>) );

    BOOST_MPL_ASSERT((meta::equal<
                      meta::filter<std::is_floating_point<mpl::_>, list4>::type,
                      meta::list<float, double>>) );

    BOOST_MPL_ASSERT(
        (meta::equal<meta::filter<std::is_pod<mpl::_>, list4>, list4>) );

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::filter<std::is_unsigned<mpl::_>, list4>, meta::list<bool>>) );

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::filter<std::is_class<mpl::_>, list4>, meta::list<>>) );

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::list_direction,
            meta::filter<std::is_floating_point<mpl::_>, meta::weird_list<>>,
            meta::weird_list<>>) );

    BOOST_MPL_ASSERT((meta::equal<
                      meta::list_direction,
                      meta::filter<std::is_floating_point<mpl::_>, weird_list4>,
                      meta::weird_list<float, double>>) );

    BOOST_MPL_ASSERT((meta::equal<
                      meta::list_direction,
                      meta::filter<std::is_class<mpl::_>, weird_list4>,
                      meta::weird_list<>>) );
}

BOOST_AUTO_TEST_SUITE_END()
