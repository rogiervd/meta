// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_equal
#include "boost/test/unit_test.hpp"

#include "list.hpp"
#include "meta/equal.hpp"

#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/size_t.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE(test_meta_range)
{
    namespace mpl = boost::mpl;

    static_assert(meta::equal<meta::list<>, meta::list<>>::value);
    static_assert(!meta::equal<meta::list<int>, meta::list<>>::value);
    static_assert(!meta::equal<meta::list<>, meta::list<int>>::value);
    static_assert(meta::equal<meta::list<int>, meta::list<int>>::value);
    static_assert(!meta::equal<meta::list<int>, meta::list<bool>>::value);
    static_assert(!meta::equal<meta::list<int, bool>, meta::list<int>>::value);
    static_assert(!meta::equal<meta::list<int>, meta::list<int, bool>>::value);
    static_assert(
        meta::equal<meta::list<int, bool>, meta::list<int, bool>>::value);
    static_assert(
        !meta::equal<meta::list<int, bool>, meta::list<int, long>>::value);
    static_assert(
        !meta::equal<meta::list<int, bool>, meta::list<long, bool>>::value);

    // With direction
    static_assert(
        meta::equal<meta::list_direction, meta::list<>, meta::list<>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::list<int>, meta::list<>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::list<>, meta::list<int>>::value);
    static_assert(
        meta::equal<
            meta::list_direction, meta::list<int>, meta::list<int>>::value);
    static_assert(
        !meta::equal<
            meta::list_direction, meta::list<long>, meta::list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::list<int, bool>,
                  meta::list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::list<int>,
                  meta::list<int, bool>>::value);
    static_assert(meta::equal<
                  meta::list_direction, meta::list<int, bool>,
                  meta::list<int, bool>>::value);

    static_assert(meta::equal<
                  meta::list_direction, meta::weird_list<>,
                  meta::weird_list<>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::weird_list<int>,
                  meta::weird_list<>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::weird_list<>,
                  meta::weird_list<int>>::value);
    static_assert(meta::equal<
                  meta::list_direction, meta::weird_list<int>,
                  meta::weird_list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::weird_list<long>,
                  meta::weird_list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::weird_list<int, bool>,
                  meta::weird_list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, meta::weird_list<int>,
                  meta::weird_list<int, bool>>::value);
    static_assert(meta::equal<
                  meta::list_direction, meta::weird_list<int, bool>,
                  meta::weird_list<int, bool>>::value);

    // With predicate
    static_assert(meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::list<>, meta::list<>>::value);
    // Don't even execute any comparison
    static_assert(!meta::equal<
                  mpl::equal_to<mpl::_, mpl::_>, meta::list<int>,
                  meta::list<>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::list<>, meta::list<int>>::value);
    static_assert(meta::equal<
                  mpl::equal_to<mpl::_, mpl::_>, meta::list<mpl::int_<3>>,
                  meta::list<mpl::size_t<3>>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::list<mpl::int_<4>>, meta::list<mpl::int_<5>>>::value);

    static_assert(meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::weird_list<>, meta::weird_list<>>::value);
    // Don't even execute any comparison
    static_assert(!meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::weird_list<>, meta::weird_list<int>>::value);
    static_assert(!meta::equal<
                  meta::list_direction, mpl::equal_to<mpl::_, mpl::_>,
                  meta::weird_list<mpl::int_<4>>,
                  meta::weird_list<mpl::int_<5>>>::value);
}

BOOST_AUTO_TEST_SUITE_END()
