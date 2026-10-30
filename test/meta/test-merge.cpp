// SPDX-FileCopyrightText: Copyright 2013 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_merge
#include "boost/test/unit_test.hpp"

#include "meta/merge.hpp"

#include <type_traits>

#include "boost/mpl/greater.hpp"

#include "list.hpp"
#include "meta/fold.hpp"
#include "meta/vector.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_merge)

BOOST_AUTO_TEST_CASE(test_meta_merge)
{
    typedef mpl::greater<mpl::_1, mpl::_2> greater;

    // default_direction.
    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::default_direction<meta::merge<
                meta::list_direction, meta::list<>, meta::list<>>>::type,
            meta::list_direction>) );

    BOOST_MPL_ASSERT((std::is_same<
                      meta::default_direction<
                          meta::merge<meta::list<>, meta::list<>>>::type,
                      meta::list_direction>) );

    // Using as_list.
    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_list<meta::merge<
                meta::list_direction, meta::list<>, meta::list<>>>::type,
            meta::list<>>) );

    BOOST_MPL_ASSERT((std::is_same<
                      meta::as_list<meta::merge<
                          meta::list_direction, meta::weird_list<mpl::int_<1>>,
                          meta::weird_list<>>>::type,
                      meta::list<mpl::int_<1>>>) );

    BOOST_MPL_ASSERT((std::is_same<
                      meta::as_list<meta::merge<
                          meta::list_direction, meta::list<>,
                          meta::list<mpl::int_<6>>>>::type,
                      meta::list<mpl::int_<6>>>) );

    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_list<meta::merge<
                meta::list<mpl::int_<5>>, meta::list<mpl::int_<6>>>>::type,
            meta::list<mpl::int_<5>, mpl::int_<6>>>) );

    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_list<meta::merge<
                meta::list_direction, greater, meta::weird_list<mpl::int_<5>>,
                meta::weird_list<mpl::int_<6>>>>::type,
            meta::list<mpl::int_<6>, mpl::int_<5>>>) );

    BOOST_MPL_ASSERT((std::is_same<
                      meta::as_list<meta::merge<
                          meta::list_direction, greater,
                          meta::list<mpl::int_<5>, mpl::int_<4>>,
                          meta::list<mpl::int_<6>>>>::type,
                      meta::list<mpl::int_<6>, mpl::int_<5>, mpl::int_<4>>>) );

    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_list<meta::merge<
                greater, meta::list<mpl::int_<6>, mpl::int_<4>>,
                meta::list<mpl::int_<5>, mpl::int_<3>>>>::type,
            meta::list<
                mpl::int_<6>, mpl::int_<5>, mpl::int_<4>, mpl::int_<3>>>) );

    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_list<meta::merge<
                meta::list_direction, greater,
                meta::weird_list<mpl::int_<6>, mpl::int_<4>>,
                meta::weird_list<mpl::int_<5>, mpl::int_<3>, mpl::int_<2>>>>::
                type,
            meta::list<
                mpl::int_<6>, mpl::int_<5>, mpl::int_<4>, mpl::int_<3>,
                mpl::int_<2>>>) );

    // Use default direction.
    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_vector<meta::merge<
                meta::vector<mpl::int_<4>, mpl::int_<5>>,
                meta::vector<mpl::int_<3>, mpl::int_<4>, mpl::int_<5>>>>::type,
            meta::vector<
                mpl::int_<3>, mpl::int_<4>, mpl::int_<4>, mpl::int_<5>,
                mpl::int_<5>>>) );

    BOOST_MPL_ASSERT(
        (std::is_same<
            meta::as_vector<meta::merge<
                greater,
                meta::vector<mpl::int_<10>, mpl::int_<4>, mpl::int_<1>>,
                meta::vector<mpl::int_<10>, mpl::int_<3>, mpl::int_<2>>>>::type,
            meta::vector<
                mpl::int_<10>, mpl::int_<10>, mpl::int_<4>, mpl::int_<3>,
                mpl::int_<2>, mpl::int_<1>>>) );
}

BOOST_AUTO_TEST_SUITE_END()
