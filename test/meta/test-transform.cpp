// SPDX-FileCopyrightText: Copyright 2011, 2012, 2014 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_transform
#include <boost/test/unit_test.hpp>

#include "list.hpp"
#include "meta/transform.hpp"

template <typename Type> struct type_wrapper {};

#include <boost/mpl/placeholders.hpp>
#include "meta/equal.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_transform)

BOOST_AUTO_TEST_CASE(test_meta_transform)
{
    using boost::mpl::_;

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::transform<type_wrapper<_>, meta::list<>>, meta::list<>>) );
    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::list_direction,
            meta::transform<type_wrapper<_>, meta::list<>>, meta::list<>>) );

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::transform<type_wrapper<_>, meta::list<int, long, bool>>,
            meta::list<
                type_wrapper<int>, type_wrapper<long>, type_wrapper<bool>>>) );
    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::list_direction,
            meta::transform<type_wrapper<_>, meta::list<int, long, bool>>,
            meta::list<
                type_wrapper<int>, type_wrapper<long>, type_wrapper<bool>>>) );

    BOOST_MPL_ASSERT(
        (meta::equal<
            meta::list_direction,
            meta::transform<type_wrapper<_>, meta::weird_list<int, long, bool>>,
            meta::weird_list<
                type_wrapper<int>, type_wrapper<long>, type_wrapper<bool>>>) );
}

BOOST_AUTO_TEST_SUITE_END()
