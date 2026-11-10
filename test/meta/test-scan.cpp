// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_scan
#include "boost/test/unit_test.hpp"

#include "list.hpp"
#include "meta/range.hpp"
#include "meta/scan.hpp"

typedef meta::list<> list0;
typedef meta::list<int, bool, float, double> list4;

typedef meta::weird_list<> weird_list0;
typedef meta::weird_list<int, bool, float, double> weird_list4;

#include <type_traits>

#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/placeholders.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_scan)

BOOST_AUTO_TEST_CASE(test_meta_scan)
{
    using boost::mpl::equal_to;
    using std::is_same_v;
    namespace mpl = boost::mpl;

    typedef meta::scan<meta::push<mpl::_2, mpl::_1>, void, list0> list_void;
    typedef meta::scan<meta::push<mpl::_2, mpl::_1>, meta::list<>, list4>
        list_list;

    // These are actually private.
    /*
    static_assert(std::is_same_v<list_list::direction, meta::list_direction>);
    static_assert(
        std::is_same_v<list_list::function, meta::push<mpl::_2, mpl::_1>>);
    static_assert(std::is_same_v<list_list::state, meta::list<>>));
    static_assert(std::is_same_v<list_list::range, list4>);
    */

    // list_void.
    static_assert(!meta::empty<list_void>::type::value);
    static_assert(boost::mpl::equal_to<
                  meta::size<list_void>, boost::mpl::size_t<1>>::value);
    static_assert(is_same_v<meta::first<list_void>::type, void>);
    static_assert(meta::empty<meta::drop<list_void>::type>::value);
    static_assert(meta::empty<meta::drop<list_void>::type>::type::value);
    static_assert(boost::mpl::equal_to<
                  meta::size<meta::drop<list_void>::type>,
                  boost::mpl::size_t<0>>::value);

    // list_list.
    static_assert(!meta::empty<list_list>::type::value);
    static_assert(boost::mpl::equal_to<
                  meta::size<list_list>, boost::mpl::size_t<5>>::value);

    static_assert(is_same_v<meta::first<list_list>::type, meta::list<>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<list_list>::type>::type, meta::list<int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<2>, list_list>::type>::type,
            meta::list<bool, int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<3>, list_list>::type>::type,
            meta::list<float, bool, int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<4>, list_list>::type>::type,
            meta::list<double, float, bool, int>>);
    static_assert(
        meta::empty<meta::drop<mpl::size_t<5>, list_list>::type>::value);

    static_assert(boost::mpl::equal_to<
                  meta::size<meta::drop<mpl::size_t<4>, list_list>::type>,
                  boost::mpl::size_t<1>>::value);
    static_assert(boost::mpl::equal_to<
                  meta::size<meta::drop<mpl::size_t<5>, list_list>::type>,
                  boost::mpl::size_t<0>>::value);

    typedef meta::scan<
        meta::list_direction,
        meta::push<meta::list_direction, mpl::_2, mpl::_1>, void, list0>
        dir_list_void;
    typedef meta::scan<
        meta::list_direction,
        meta::push<meta::list_direction, mpl::_2, mpl::_1>, meta::list<>, list4>
        dir_list_list;

    static_assert(is_same_v<meta::first<dir_list_void>::type, void>);
    static_assert(meta::empty<meta::drop<dir_list_void>::type>::value);

    static_assert(is_same_v<meta::first<dir_list_list>::type, meta::list<>>);
    static_assert(is_same_v<
                  meta::first<meta::drop<dir_list_list>::type>::type,
                  meta::list<int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<2>, dir_list_list>::type>::type,
            meta::list<bool, int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<3>, dir_list_list>::type>::type,
            meta::list<float, bool, int>>);
    static_assert(
        is_same_v<
            meta::first<meta::drop<mpl::size_t<4>, dir_list_list>::type>::type,
            meta::list<double, float, bool, int>>);
    static_assert(
        meta::empty<meta::drop<mpl::size_t<5>, dir_list_list>::type>::value);

    typedef meta::scan<
        meta::list_direction,
        meta::push<meta::list_direction, mpl::_2, mpl::_1>, void, weird_list0>
        weird_list_void;
    typedef meta::scan<
        meta::list_direction,
        meta::push<meta::list_direction, mpl::_2, mpl::_1>, meta::weird_list<>,
        weird_list4>
        weird_list_list;

    static_assert(is_same_v<meta::first<weird_list_void>::type, void>);
    static_assert(meta::empty<meta::drop<weird_list_void>::type>::value);

    static_assert(
        is_same_v<meta::first<weird_list_list>::type, meta::weird_list<>>);
    static_assert(is_same_v<
                  meta::first<meta::drop<weird_list_list>::type>::type,
                  meta::weird_list<int>>);
    static_assert(is_same_v<
                  meta::first<
                      meta::drop<mpl::size_t<2>, weird_list_list>::type>::type,
                  meta::weird_list<bool, int>>);
    static_assert(is_same_v<
                  meta::first<
                      meta::drop<mpl::size_t<3>, weird_list_list>::type>::type,
                  meta::weird_list<float, bool, int>>);
    static_assert(is_same_v<
                  meta::first<
                      meta::drop<mpl::size_t<4>, weird_list_list>::type>::type,
                  meta::weird_list<double, float, bool, int>>);
    static_assert(
        meta::empty<meta::drop<mpl::size_t<5>, weird_list_list>::type>::value);
}

BOOST_AUTO_TEST_SUITE_END()
