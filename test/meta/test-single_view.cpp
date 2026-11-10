// SPDX-FileCopyrightText: Copyright 2013 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_single_view
#include "boost/test/unit_test.hpp"

#include "meta/single_view.hpp"

#include <type_traits>

#include "boost/mpl/equal_to.hpp"

#include "meta/empty_view.hpp"
#include "meta/range.hpp"

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_single_view)

BOOST_AUTO_TEST_CASE(test_meta_single_view)
{
    // Specify direction.
    {
        typedef meta::single_view<meta::list_direction, int> v;

        static_assert(std::is_same_v<
                      meta::default_direction<v>::type, meta::list_direction>);

        static_assert(!meta::empty<v>::value);
        static_assert(!meta::empty<meta::list_direction, v>::value);

        static_assert(
            boost::mpl::equal_to<meta::size<v>, boost::mpl::size_t<1>>::value);
        static_assert(boost::mpl::equal_to<
                      meta::size<meta::list_direction, v>,
                      boost::mpl::size_t<1>>::value);

        static_assert(std::is_same_v<meta::first<v>::type, int>);
        static_assert(
            std::is_same_v<meta::first<meta::list_direction, v>::type, int>);

        // The result of drop <single_view <...> is not defined to be an
        // empty_view.
        // But then, if the following passes, then it is left to empty_view.cpp
        // to test its behaviour.
        static_assert(
            std::is_same_v<
                meta::drop<v>::type, meta::empty_view<meta::list_direction>>);
        static_assert(std::is_same_v<
                      meta::drop<meta::list_direction, v>::type,
                      meta::empty_view<meta::list_direction>>);
    }
    // Don't specify direction: should be "front".
    {
        typedef meta::single_view<bool> v;

        static_assert(
            std::is_same_v<meta::default_direction<v>::type, meta::front>);

        static_assert(!meta::empty<v>::value);
        static_assert(!meta::empty<meta::front, v>::value);

        static_assert(
            boost::mpl::equal_to<meta::size<v>, boost::mpl::size_t<1>>::value);
        static_assert(
            boost::mpl::equal_to<
                meta::size<meta::front, v>, boost::mpl::size_t<1>>::value);

        static_assert(std::is_same_v<meta::first<v>::type, bool>);
        static_assert(std::is_same_v<meta::first<meta::front, v>::type, bool>);

        static_assert(
            std::is_same_v<meta::drop<v>::type, meta::empty_view<meta::front>>);
        static_assert(std::is_same_v<
                      meta::drop<meta::front, v>::type,
                      meta::empty_view<meta::front>>);
    }
}

BOOST_AUTO_TEST_SUITE_END()
