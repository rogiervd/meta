// SPDX-FileCopyrightText: Copyright 2014, 2015 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE set
#include "boost/test/unit_test.hpp"

#include <type_traits>

#include "meta/contains.hpp"
#include "meta/range.hpp"
#include "meta/set.hpp"

#include "boost/mpl/equal.hpp"
#include "meta/vector.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_set)

typedef meta::set<> set_0;
typedef meta::set<int> set_1;
typedef meta::set<bool, int> set_2;

BOOST_AUTO_TEST_CASE(test_meta_set)
{
    // empty.
    static_assert(meta::empty<set_0>::value);
    static_assert(!meta::empty<set_1>::value);
    static_assert(!meta::empty<set_2>::value);

    // size.
    static_assert(
        boost::mpl::equal<meta::size<set_0>, boost::mpl::size_t<0>>::value);
    static_assert(
        boost::mpl::equal<meta::size<set_1>, boost::mpl::size_t<1>>::value);
    static_assert(
        boost::mpl::equal<meta::size<set_2>, boost::mpl::size_t<2>>::value);

    // first.
    static_assert(std::is_same_v<typename meta::first<set_1>::type, int>);
    static_assert(std::is_same_v<typename meta::first<set_2>::type, bool>);

    // drop.
    static_assert(std::is_same_v<typename meta::drop<set_1>::type, set_0>);
    static_assert(std::is_same_v<typename meta::drop<set_2>::type, set_1>);

    // push.
    static_assert(std::is_same_v<typename meta::push<int, set_0>::type, set_1>);
    static_assert(
        std::is_same_v<typename meta::push<bool, set_1>::type, set_2>);

    // contains.
    static_assert(!meta::contains<int, set_0>::value);
    static_assert(!meta::contains<bool, set_0>::value);
    static_assert(!meta::contains<long, set_0>::value);

    static_assert(meta::contains<int, set_1>::value);
    static_assert(!meta::contains<bool, set_1>::value);
    static_assert(!meta::contains<long, set_1>::value);

    static_assert(meta::contains<int, set_2>::value);
    static_assert(meta::contains<bool, set_2>::value);
    static_assert(!meta::contains<long, set_2>::value);

    // has_key: the same as contains.
    static_assert(!meta::has_key<int, set_0>::value);
    static_assert(!meta::has_key<bool, set_0>::value);
    static_assert(!meta::has_key<long, set_0>::value);

    static_assert(meta::has_key<int, set_1>::value);
    static_assert(!meta::has_key<bool, set_1>::value);
    static_assert(!meta::has_key<long, set_1>::value);

    static_assert(meta::has_key<int, set_2>::value);
    static_assert(meta::has_key<bool, set_2>::value);
    static_assert(!meta::has_key<long, set_2>::value);

    // insert: new element.
    static_assert(
        std::is_same_v<typename meta::insert<int, set_0>::type, set_1>);
    static_assert(
        std::is_same_v<typename meta::insert<bool, set_1>::type, set_2>);
    // Existing element.
    static_assert(
        std::is_same_v<typename meta::insert<int, set_1>::type, set_1>);
    static_assert(
        std::is_same_v<typename meta::insert<int, set_2>::type, set_2>);
    static_assert(
        std::is_same_v<typename meta::insert<bool, set_2>::type, set_2>);

    // remove.
    static_assert(
        std::is_same_v<typename meta::remove<int, set_1>::type, set_0>);
    static_assert(
        std::is_same_v<typename meta::remove<bool, set_2>::type, set_1>);
}

BOOST_AUTO_TEST_CASE(test_meta_as_set)
{
    /*{
        // Causes an error because a set cannot contain the same element twice.
        typedef meta::set <int, long, int> s;
        typename meta::contains <int, s>::type l;
    }*/
    {
        static_assert(
            std::is_same_v<
                typename meta::as_set<meta::vector<>>::type, meta::set<>>);
        static_assert(std::is_same_v<
                      typename meta::as_set<meta::vector<int>>::type,
                      meta::set<int>>);
        static_assert(std::is_same_v<
                      typename meta::as_set<meta::vector<int, bool>>::type,
                      meta::set<int, bool>>);

        // Duplicate elements are represented only once.
        static_assert(std::is_same_v<
                      typename meta::as_set<meta::vector<int, bool, int>>::type,
                      meta::set<bool, int>>);
        static_assert(
            std::is_same_v<
                typename meta::as_set<meta::vector<int, int, bool, int>>::type,
                meta::set<bool, int>>);
    }
}

BOOST_AUTO_TEST_CASE(test_meta_is_subset)
{
    static_assert(meta::is_subset<meta::set<>, meta::set<>>::value);
    static_assert(!meta::is_subset<meta::set<int>, meta::set<>>::value);
    static_assert(meta::is_subset<meta::set<>, meta::set<int>>::value);
    static_assert(meta::is_subset<meta::set<int>, meta::set<int>>::value);

    static_assert(meta::is_subset<meta::set<>, meta::set<bool>>::value);
    static_assert(!meta::is_subset<meta::set<int>, meta::set<bool>>::value);
    static_assert(meta::is_subset<meta::set<>, meta::set<int, bool>>::value);
    static_assert(meta::is_subset<meta::set<int>, meta::set<bool, int>>::value);

    static_assert(meta::is_subset<meta::set<bool>, meta::set<bool>>::value);
    static_assert(
        !meta::is_subset<meta::set<int, bool>, meta::set<bool>>::value);
    static_assert(
        meta::is_subset<meta::set<bool>, meta::set<int, bool>>::value);
    static_assert(
        meta::is_subset<meta::set<int, bool>, meta::set<bool, int>>::value);

    static_assert(
        meta::is_subset<meta::set<bool, float>, meta::set<bool, float>>::value);
    static_assert(!meta::is_subset<
                  meta::set<int, bool, float>, meta::set<float, bool>>::value);
    static_assert(meta::is_subset<
                  meta::set<bool, float>, meta::set<int, float, bool>>::value);
    static_assert(
        meta::is_subset<
            meta::set<int, float, bool>, meta::set<bool, float, int>>::value);
}

BOOST_AUTO_TEST_SUITE_END()
