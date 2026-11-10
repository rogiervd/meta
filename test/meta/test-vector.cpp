// SPDX-FileCopyrightText: Copyright 2011, 2012, 2015 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_vector
#include "boost/test/unit_test.hpp"

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/vector.hpp"

typedef meta::vector<> vector0;
typedef meta::vector<int> vector1;
typedef meta::vector<int, bool> vector2;
typedef meta::vector<int, bool, float, double> vector4;

#include <type_traits>

#include "boost/mpl/equal_to.hpp"

#include "boost/mpl/placeholders.hpp"

#include "meta/concatenate.hpp"

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_vector)

BOOST_AUTO_TEST_CASE(test_meta_vector)
{
    using boost::mpl::equal_to;
    using std::is_same_v;
    namespace mpl = boost::mpl;

    static_assert(meta::empty<vector0>::value);
    static_assert(meta::empty<meta::back, vector0>::value);
    static_assert(!meta::empty<vector1>::value);
    static_assert(!meta::empty<meta::back, vector2>::value);
    static_assert(!meta::empty<vector4>::value);

    static_assert(equal_to<meta::size<vector0>, mpl::size_t<0>>::value);
    static_assert(equal_to<meta::size<vector1>, mpl::size_t<1>>::value);
    static_assert(
        equal_to<meta::size<meta::back, vector1>, mpl::size_t<1>>::value);
    static_assert(equal_to<meta::size<vector4>, mpl::size_t<4>>::value);

    static_assert(is_same_v<meta::first<vector1>::type, int>);
    static_assert(is_same_v<meta::first<meta::back, vector1>::type, int>);
    static_assert(is_same_v<meta::first<vector2>::type, int>);
    static_assert(is_same_v<meta::first<meta::back, vector2>::type, bool>);
    static_assert(is_same_v<meta::first<vector4>::type, int>);
    static_assert(is_same_v<meta::first<meta::back, vector4>::type, double>);

    static_assert(
        is_same_v<meta::drop<mpl::size_t<0>, vector0>::type, vector0>);
    static_assert(
        is_same_v<
            meta::drop<meta::back, mpl::size_t<0>, vector0>::type, vector0>);

    static_assert(
        is_same_v<meta::drop<mpl::size_t<0>, vector1>::type, vector1>);
    static_assert(
        is_same_v<
            meta::drop<meta::back, mpl::size_t<0>, vector1>::type, vector1>);

    static_assert(
        is_same_v<meta::drop<mpl::size_t<1>, vector1>::type, vector0>);
    static_assert(
        is_same_v<
            meta::drop<meta::back, mpl::size_t<1>, vector1>::type, vector0>);

    static_assert(is_same_v<
                  meta::drop<mpl::size_t<2>, vector4>::type,
                  meta::vector<float, double>>);
    static_assert(is_same_v<
                  meta::drop<meta::back, mpl::size_t<2>, vector4>::type,
                  meta::vector<int, bool>>);

    static_assert(is_same_v<meta::push<int, vector0>::type, meta::vector<int>>);
    static_assert(
        is_same_v<
            meta::push<meta::back, int, vector0>::type, meta::vector<int>>);
    static_assert(
        is_same_v<meta::push<bool, vector1>::type, meta::vector<bool, int>>);
    static_assert(is_same_v<
                  meta::push<meta::back, bool, vector1>::type,
                  meta::vector<int, bool>>);
    static_assert(is_same_v<
                  meta::push<void, vector4>::type,
                  meta::vector<void, int, bool, float, double>>);
    static_assert(is_same_v<
                  meta::push<meta::back, void, vector4>::type,
                  meta::vector<int, bool, float, double, void>>);
}

// Algorithm specialisation for vector

template <typename Type> struct type_wrapper {};

BOOST_AUTO_TEST_CASE(test_meta_transform_vector)
{
    using boost::mpl::_1;
    using std::is_same_v;

    static_assert(is_same_v<
                  meta::as_vector<
                      meta::transform<type_wrapper<_1>, meta::vector<>>>::type,
                  meta::vector<>>);

    static_assert(
        is_same_v<
            meta::as_vector<meta::transform<
                type_wrapper<_1>, meta::vector<int, long, bool>>>::type,
            meta::vector<
                type_wrapper<int>, type_wrapper<long>, type_wrapper<bool>>>);
}

BOOST_AUTO_TEST_CASE(test_meta_concatenate_vector)
{
    using std::is_same_v;

    static_assert(is_same_v<
                  meta::concatenate<meta::vector<>, meta::vector<>>::type,
                  meta::vector<>>);
    static_assert(is_same_v<
                  meta::concatenate<meta::vector<int>, meta::vector<>>::type,
                  meta::vector<int>>);
    static_assert(is_same_v<
                  meta::concatenate<meta::vector<>, meta::vector<int>>::type,
                  meta::vector<int>>);
    static_assert(
        is_same_v<
            meta::concatenate<meta::vector<int>, meta::vector<bool>>::type,
            meta::vector<int, bool>>);
    static_assert(is_same_v<
                  meta::concatenate<
                      meta::vector<int, float>, meta::vector<bool>>::type,
                  meta::vector<int, float, bool>>);
    static_assert(is_same_v<
                  meta::concatenate<
                      meta::vector<int>, meta::vector<bool, float>>::type,
                  meta::vector<int, bool, float>>);
}

BOOST_AUTO_TEST_CASE(test_meta_as_vector)
{
    using std::is_same_v;

    static_assert(
        is_same_v<meta::as_vector<meta::list<>>::type, meta::vector<>>);
    static_assert(
        is_same_v<meta::as_vector<meta::list<int>>::type, meta::vector<int>>);
    static_assert(is_same_v<
                  meta::as_vector<meta::list<int, float>>::type,
                  meta::vector<int, float>>);
    static_assert(is_same_v<
                  meta::as_vector<meta::list<int, float, bool>>::type,
                  meta::vector<int, float, bool>>);

    static_assert(is_same_v<
                  meta::as_vector<
                      meta::list_direction, meta::weird_list<int, float>>::type,
                  meta::vector<int, float>>);

    // There is a specialisation for meta::vector itself.
    static_assert(
        is_same_v<meta::as_vector<meta::vector<>>::type, meta::vector<>>);
    static_assert(
        is_same_v<meta::as_vector<meta::vector<int>>::type, meta::vector<int>>);
    static_assert(is_same_v<
                  meta::as_vector<meta::vector<int, float>>::type,
                  meta::vector<int, float>>);
}

BOOST_AUTO_TEST_CASE(test_meta_split_vector)
{
    static_assert(std::is_same_v<
                  meta::tail_of_longer<meta::vector<>, meta::vector<>>::type,
                  meta::vector<>>);
    static_assert(std::is_same_v<
                  meta::tail_of_longer<meta::vector<>, meta::vector<int>>::type,
                  meta::vector<int>>);
    static_assert(std::is_same_v<
                  meta::tail_of_longer<
                      meta::vector<int>, meta::vector<bool, int>>::type,
                  meta::vector<int>>);
    static_assert(std::is_same_v<
                  meta::tail_of_longer<
                      meta::vector<int>, meta::vector<bool, long, int>>::type,
                  meta::vector<long, int>>);
    static_assert(
        std::is_same_v<
            meta::tail_of_longer<
                meta::vector<int, long>, meta::vector<bool, long, int>>::type,
            meta::vector<int>>);
}

BOOST_AUTO_TEST_SUITE_END()
