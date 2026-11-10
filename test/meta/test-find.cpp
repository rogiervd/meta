// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_find
#include "boost/test/unit_test.hpp"

#include "boost/mpl/for_each.hpp"

#include "list.hpp"
#include "meta/find.hpp"

typedef meta::list<> list0;
typedef meta::list<int, bool, float, double> list4;

typedef meta::weird_list<> weird_list0;
typedef meta::weird_list<int, bool, float, double> weird_list4;

#include <type_traits>


BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE(test_meta_find)
{
    using std::is_same_v;
    namespace mpl = boost::mpl;

    static_assert(
        is_same_v<
            meta::find<std::is_floating_point<mpl::_>, meta::list<>>::type,
            meta::list<>>);

    static_assert(is_same_v<
                  meta::find<std::is_floating_point<mpl::_>, list4>::type,
                  meta::list<float, double>>);

    static_assert(
        is_same_v<meta::find<std::is_pod<mpl::_>, list4>::type, list4>);

    static_assert(is_same_v<
                  meta::find<std::is_unsigned<mpl::_>, list4>::type,
                  meta::list<bool, float, double>>);

    static_assert(
        is_same_v<
            meta::find<std::is_class<mpl::_>, list4>::type, meta::list<>>);

    static_assert(is_same_v<
                  meta::find<
                      meta::list_direction, std::is_floating_point<mpl::_>,
                      meta::weird_list<>>::type,
                  meta::weird_list<>>);

    static_assert(
        is_same_v<
            meta::find<
                meta::list_direction, std::is_pod<mpl::_>, weird_list4>::type,
            weird_list4>);

    static_assert(is_same_v<
                  meta::find<
                      meta::list_direction, std::is_unsigned<mpl::_>,
                      weird_list4>::type,
                  meta::weird_list<bool, float, double>>);

    static_assert(
        is_same_v<
            meta::find<
                meta::list_direction, std::is_class<mpl::_>, weird_list4>::type,
            meta::weird_list<>>);
}

BOOST_AUTO_TEST_SUITE_END()
