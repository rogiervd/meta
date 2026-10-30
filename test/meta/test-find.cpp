// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_find
#include "boost/test/unit_test.hpp"

#include "list.hpp"
#include "meta/find.hpp"

typedef meta::list<> list0;
typedef meta::list<int, bool, float, double> list4;

typedef meta::weird_list<> weird_list0;
typedef meta::weird_list<int, bool, float, double> weird_list4;

#include <type_traits>

#include "boost/mpl/assert.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE(test_meta_find)
{
    using std::is_same;
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT(
        (is_same<
            meta::find<std::is_floating_point<mpl::_>, meta::list<>>::type,
            meta::list<>>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::find<std::is_floating_point<mpl::_>, list4>::type,
                      meta::list<float, double>>) );

    BOOST_MPL_ASSERT(
        (is_same<meta::find<std::is_pod<mpl::_>, list4>::type, list4>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::find<std::is_unsigned<mpl::_>, list4>::type,
                      meta::list<bool, float, double>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::find<std::is_class<mpl::_>, list4>::type, meta::list<>>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::find<
                          meta::list_direction, std::is_floating_point<mpl::_>,
                          meta::weird_list<>>::type,
                      meta::weird_list<>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::find<
                meta::list_direction, std::is_pod<mpl::_>, weird_list4>::type,
            weird_list4>) );

    BOOST_MPL_ASSERT((is_same<
                      meta::find<
                          meta::list_direction, std::is_unsigned<mpl::_>,
                          weird_list4>::type,
                      meta::weird_list<bool, float, double>>) );

    BOOST_MPL_ASSERT(
        (is_same<
            meta::find<
                meta::list_direction, std::is_class<mpl::_>, weird_list4>::type,
            meta::weird_list<>>) );
}

BOOST_AUTO_TEST_SUITE_END()
