// SPDX-FileCopyrightText: Copyright 2013 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_empty_view
#include "boost/test/unit_test.hpp"

#include "meta/empty_view.hpp"

#include <type_traits>


#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_empty_view)

BOOST_AUTO_TEST_CASE(test_meta_empty_view)
{
    // Specify direction.
    {
        typedef meta::empty_view<meta::list_direction> v;

        static_assert(std::is_same_v<
                      meta::default_direction<v>::type, meta::list_direction>);

        static_assert(meta::empty<v>::value);
        static_assert(meta::empty<meta::list_direction, v>::value);

        static_assert(
            boost::mpl::equal_to<meta::size<v>, boost::mpl::size_t<0>>::value);
        static_assert(boost::mpl::equal_to<
                      meta::size<meta::list_direction, v>,
                      boost::mpl::size_t<0>>::value);
    }
    // Don't specify direction: should be "front".
    {
        typedef meta::empty_view<> v;

        static_assert(
            std::is_same_v<meta::default_direction<v>::type, meta::front>);

        static_assert(meta::empty<v>::value);
        static_assert(meta::empty<meta::front, v>::value);

        static_assert(
            boost::mpl::equal_to<meta::size<v>, boost::mpl::size_t<0>>::value);
        static_assert(
            boost::mpl::equal_to<
                meta::size<meta::front, v>, boost::mpl::size_t<0>>::value);
    }
}

BOOST_AUTO_TEST_SUITE_END()
