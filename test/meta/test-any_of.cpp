// SPDX-FileCopyrightText: Copyright 2013, 2015 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_any
#include <boost/test/unit_test.hpp>

#include "meta/any_of.hpp"

#include <boost/mpl/bool.hpp>  // IWYU pragma: keep
#include "list.hpp"

#include "meta/fwd.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_any_of)

BOOST_AUTO_TEST_CASE(test_meta_any_of)
{
    namespace mpl = boost::mpl;

    static_assert(!meta::any_of<meta::list<>>::value, "");

    static_assert(!meta::any_of<meta::list<mpl::false_>>::value, "");
    static_assert(meta::any_of<meta::list<mpl::true_>>::value, "");

    static_assert(
        !meta::any_of<meta::list<mpl::false_, mpl::false_>>::value, "");
    static_assert(meta::any_of<meta::list<mpl::false_, mpl::true_>>::value, "");
    static_assert(meta::any_of<meta::list<mpl::true_, mpl::false_>>::value, "");
    static_assert(meta::any_of<meta::list<mpl::true_, mpl::true_>>::value, "");

    // Short-circuit.
    static_assert(meta::any_of<meta::list<mpl::true_, int>>::value, "");
    static_assert(meta::any_of<meta::list<mpl::true_, int, bool>>::value, "");

    // weird_list
    static_assert(
        !meta::any_of<meta::list_direction, meta::weird_list<>>::value, "");

    static_assert(
        !meta::any_of<
            meta::list_direction,
            meta::weird_list<mpl::false_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<
            meta::list_direction,
            meta::weird_list<mpl::false_, mpl::true_>>::value,
        "");
    static_assert(
        meta::any_of<
            meta::list_direction,
            meta::weird_list<mpl::true_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<
            meta::list_direction,
            meta::weird_list<mpl::true_, mpl::true_>>::value,
        "");
}

// Without including meta/vector.hpp!
// This should just use the type.
BOOST_AUTO_TEST_CASE(test_meta_any_of_vector)
{
    static_assert(!meta::any_of<meta::vector<>>::value, "");

    static_assert(!meta::any_of<meta::vector<mpl::false_>>::value, "");
    static_assert(meta::any_of<meta::vector<mpl::true_>>::value, "");

    static_assert(
        !meta::any_of<meta::vector<mpl::false_, mpl::false_>>::value, "");
    static_assert(
        meta::any_of<meta::vector<mpl::false_, mpl::true_>>::value, "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::false_>>::value, "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::true_>>::value, "");

    static_assert(
        !meta::any_of<
            meta::vector<mpl::false_, mpl::false_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::false_, mpl::false_, mpl::true_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::false_, mpl::true_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::false_, mpl::true_, mpl::true_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::false_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::false_, mpl::true_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::true_, mpl::false_>>::value,
        "");
    static_assert(
        meta::any_of<meta::vector<mpl::true_, mpl::true_, mpl::true_>>::value,
        "");

    // Short-circuit.
    static_assert(meta::any_of<meta::vector<mpl::true_, int>>::value, "");
    static_assert(meta::any_of<meta::vector<mpl::true_, int, bool>>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
