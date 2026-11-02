// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#define BOOST_TEST_MODULE test_meta_vector_mpl
#include "boost/test/unit_test.hpp"

#include "meta/vector.hpp"

#include <type_traits>

#include "boost/mpl/equal_to.hpp"

#include "boost/mpl/at.hpp"
#include "boost/mpl/back.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/pop_back.hpp"
#include "boost/mpl/pop_front.hpp"

#include "boost/mpl/erase.hpp"
#include "boost/mpl/insert.hpp"
#include "boost/mpl/insert_range.hpp"

#include "boost/mpl/advance.hpp"
#include "boost/mpl/deref.hpp"
#include "boost/mpl/distance.hpp"

#include "boost/mpl/copy_if.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/transform.hpp"

typedef meta::vector<> vector0;
typedef meta::vector<int> vector1;
typedef meta::vector<int, bool> vector2;
typedef meta::vector<int, bool, float, double> vector4;

BOOST_AUTO_TEST_SUITE(test_meta_vector_mpl)

BOOST_AUTO_TEST_CASE(test_meta_vector_mpl)
{
    using namespace boost::mpl;

    static_assert(empty<vector0>::value);
    static_assert(!empty<vector1>::value);
    static_assert(!empty<vector4>::value);

    static_assert(equal_to<size<vector0>, int_<0>>::value);
    static_assert(equal_to<size<vector1>, int_<1>>::value);
    static_assert(equal_to<size<vector4>, int_<4>>::value);

    static_assert(std::is_same_v<front<vector1>::type, int>);
    static_assert(std::is_same_v<front<vector4>::type, int>);
    static_assert(std::is_same_v<back<vector1>::type, int>);
    static_assert(std::is_same_v<back<vector4>::type, double>);

    // The following are not necessarily true for all Front Extensible
    // MPL Sequences but for meta::vector it is a requirement.
    static_assert(
        std::is_same_v<push_front<vector0, long>::type, meta::vector<long>>);
    static_assert(std::is_same_v<
                  push_front<vector1, long>::type, meta::vector<long, int>>);
    static_assert(
        std::is_same_v<
            push_front<vector2, long>::type, meta::vector<long, int, bool>>);
    static_assert(std::is_same_v<
                  push_front<vector4, long>::type,
                  meta::vector<long, int, bool, float, double>>);

    static_assert(std::is_same_v<pop_front<vector1>::type, meta::vector<>>);
    static_assert(std::is_same_v<
                  pop_front<vector4>::type, meta::vector<bool, float, double>>);

    static_assert(
        std::is_same_v<push_back<vector0, long>::type, meta::vector<long>>);
    static_assert(std::is_same_v<
                  push_back<vector1, long>::type, meta::vector<int, long>>);
    static_assert(
        std::is_same_v<
            push_back<vector2, long>::type, meta::vector<int, bool, long>>);
    static_assert(std::is_same_v<
                  push_back<vector4, long>::type,
                  meta::vector<int, bool, float, double, long>>);

    static_assert(std::is_same_v<pop_back<vector1>::type, meta::vector<>>);
    static_assert(std::is_same_v<pop_back<vector2>::type, meta::vector<int>>);
    static_assert(std::is_same_v<
                  pop_back<vector4>::type, meta::vector<int, bool, float>>);

    static_assert(std::is_same_v<at<vector1, int_<0>>::type, int>);
    static_assert(std::is_same_v<at<vector2, int_<0>>::type, int>);
    static_assert(std::is_same_v<at<vector2, int_<1>>::type, bool>);
    static_assert(std::is_same_v<at<vector4, int_<0>>::type, int>);
    static_assert(std::is_same_v<at<vector4, int_<1>>::type, bool>);
    static_assert(std::is_same_v<at<vector4, int_<2>>::type, float>);
    static_assert(std::is_same_v<at<vector4, int_<3>>::type, double>);
}

BOOST_AUTO_TEST_CASE(test_meta_vector_mpl_iterators)
{
    using namespace boost::mpl;

    static_assert(std::is_same_v<begin<vector0>::type, end<vector0>::type>);

    static_assert(
        std::is_same_v<next<begin<vector1>::type>::type, end<vector1>::type>);
    static_assert(
        std::is_same_v<begin<vector1>::type, prior<end<vector1>::type>::type>);
    static_assert(
        std::is_same_v<
            next<begin<vector2>::type>::type, prior<end<vector2>::type>::type>);
    static_assert(std::is_same_v<
                  next<begin<vector4>::type>::type,
                  prior<prior<prior<end<vector4>::type>::type>::type>::type>);
    static_assert(
        std::is_same_v<
            next<
                next<next<next<begin<vector4>::type>::type>::type>::type>::type,
            end<vector4>::type>);
    static_assert(std::is_same_v<
                  deref<next<begin<vector4>::type>::type>::type,
                  deref<advance<end<vector4>::type, int_<-3>>::type>::type>);
    static_assert(std::is_same_v<
                  deref<advance<begin<vector4>::type, int_<2>>::type>::type,
                  deref<advance<end<vector4>::type, int_<-2>>::type>::type>);

    static_assert(std::is_same_v<deref<begin<vector1>::type>::type, int>);

    static_assert(std::is_same_v<deref<begin<vector4>::type>::type, int>);
    static_assert(
        std::is_same_v<deref<next<begin<vector4>::type>::type>::type, bool>);
    static_assert(
        std::is_same_v<
            deref<next<next<begin<vector4>::type>::type>::type>::type, float>);
    static_assert(
        std::is_same_v<
            deref<
                next<next<next<begin<vector4>::type>::type>::type>::type>::type,
            double>);

    static_assert(equal_to<
                  distance<begin<vector0>::type, end<vector0>::type>::type,
                  boost::mpl::size_t<0>>::value);
    static_assert(equal_to<
                  distance<begin<vector1>::type, end<vector1>::type>::type,
                  boost::mpl::size_t<1>>::value);
    static_assert(equal_to<
                  distance<begin<vector4>::type, end<vector4>::type>::type,
                  boost::mpl::size_t<4>>::value);
    static_assert(
        equal_to<
            distance<
                next<begin<vector4>::type>::type, end<vector4>::type>::type,
            boost::mpl::size_t<3>>::value);
    static_assert(equal_to<
                  distance<
                      next<begin<vector4>::type>::type,
                      prior<end<vector4>::type>::type>::type,
                  boost::mpl::size_t<2>>::value);
}

BOOST_AUTO_TEST_CASE(test_meta_vector_with_mpl_iterators)
{
    using namespace boost::mpl;

    // erase
    static_assert(
        std::is_same_v<erase<vector1, begin<vector1>::type>::type, vector0>);
    static_assert(
        std::is_same_v<
            erase<vector2, begin<vector2>::type>::type, meta::vector<bool>>);
    static_assert(
        std::is_same_v<
            erase<vector2, next<begin<vector2>::type>::type>::type, vector1>);
    static_assert(std::is_same_v<
                  erase<vector4, next<begin<vector4>::type>::type>::type,
                  meta::vector<int, float, double>>);
    static_assert(std::is_same_v<
                  erase<vector4, prior<end<vector4>::type>::type>::type,
                  meta::vector<int, bool, float>>);

    // erase with range
    static_assert(
        std::is_same_v<
            erase<vector0, begin<vector0>::type, begin<vector0>::type>::type,
            vector0>);
    static_assert(
        std::is_same_v<
            erase<vector1, begin<vector1>::type, begin<vector1>::type>::type,
            vector1>);
    static_assert(
        std::is_same_v<
            erase<vector1, begin<vector1>::type, end<vector1>::type>::type,
            vector0>);
    static_assert(
        std::is_same_v<
            erase<vector2, begin<vector2>::type, begin<vector2>::type>::type,
            vector2>);
    static_assert(std::is_same_v<
                  erase<
                      vector2, begin<vector2>::type,
                      next<begin<vector2>::type>::type>::type,
                  meta::vector<bool>>);
    static_assert(
        std::is_same_v<
            erase<vector2, begin<vector2>::type, end<vector2>::type>::type,
            vector0>);
    static_assert(std::is_same_v<
                  erase<
                      vector4, next<begin<vector4>::type>::type,
                      prior<end<vector4>::type>::type>::type,
                  meta::vector<int, double>>);

    // insert
    static_assert(std::is_same_v<
                  insert<vector0, begin<vector0>::type, int>::type,
                  meta::vector<int>>);

    static_assert(std::is_same_v<
                  insert<vector1, begin<vector1>::type, bool>::type,
                  meta::vector<bool, int>>);
    static_assert(std::is_same_v<
                  insert<vector1, end<vector1>::type, bool>::type,
                  meta::vector<int, bool>>);

    static_assert(std::is_same_v<
                  insert<vector2, begin<vector2>::type, float>::type,
                  meta::vector<float, int, bool>>);
    static_assert(
        std::is_same_v<
            insert<vector2, next<begin<vector2>::type>::type, float>::type,
            meta::vector<int, float, bool>>);
    static_assert(std::is_same_v<
                  insert<vector2, end<vector2>::type, float>::type,
                  meta::vector<int, bool, float>>);

    // insert_range
    static_assert(std::is_same_v<
                  insert_range<vector0, begin<vector0>::type, vector0>::type,
                  meta::vector<>>);
    static_assert(std::is_same_v<
                  insert_range<vector0, begin<vector0>::type, vector2>::type,
                  vector2>);

    static_assert(std::is_same_v<
                  insert_range<vector1, begin<vector1>::type, vector0>::type,
                  vector1>);
    static_assert(std::is_same_v<
                  insert_range<vector1, begin<vector1>::type, vector2>::type,
                  meta::vector<int, bool, int>>);
    static_assert(std::is_same_v<
                  insert_range<vector1, end<vector1>::type, vector2>::type,
                  meta::vector<int, int, bool>>);

    static_assert(std::is_same_v<
                  insert_range<vector2, begin<vector2>::type, vector0>::type,
                  vector2>);
    static_assert(std::is_same_v<
                  insert_range<
                      vector2, next<begin<vector2>::type>::type, vector0>::type,
                  vector2>);
    static_assert(
        std::is_same_v<
            insert_range<vector2, end<vector2>::type, vector0>::type, vector2>);

    static_assert(std::is_same_v<
                  insert_range<vector2, begin<vector2>::type, vector4>::type,
                  meta::vector<int, bool, float, double, int, bool>>);
    static_assert(std::is_same_v<
                  insert_range<
                      vector2, next<begin<vector2>::type>::type, vector4>::type,
                  meta::vector<int, int, bool, float, double, bool>>);
    static_assert(std::is_same_v<
                  insert_range<vector2, end<vector2>::type, vector4>::type,
                  meta::vector<int, bool, int, bool, float, double>>);
}

template <typename Type> struct wrapped;

template <typename Type> struct wrap
{
    typedef wrapped<Type> type;
};

struct converted;

BOOST_AUTO_TEST_CASE(test_meta_vector_mpl_algorithms)
{
    using namespace boost::mpl;

    static_assert(
        std::is_same_v<transform<vector0, wrapped<_>>::type, meta::vector<>>);
    static_assert(
        std::is_same_v<
            transform<vector1, wrapped<_>>::type, meta::vector<wrapped<int>>>);
    static_assert(
        std::is_same_v<
            transform<vector4, wrapped<_>>::type,
            meta::vector<
                wrapped<int>, wrapped<bool>, wrapped<float>, wrapped<double>>>);

    static_assert(
        std::is_same_v<transform<vector0, wrap<_>>::type, meta::vector<>>);
    static_assert(
        std::is_same_v<
            transform<vector1, wrap<_>>::type, meta::vector<wrapped<int>>>);
    static_assert(
        std::is_same_v<
            transform<vector4, wrap<_>>::type,
            meta::vector<
                wrapped<int>, wrapped<bool>, wrapped<float>, wrapped<double>>>);

    static_assert(std::is_same_v<
                  copy_if<vector4, std::is_same<float, _>>::type,
                  meta::vector<float>>);

    static_assert(
        std::is_same_v<
            copy_if<
                meta::vector<
                    meta::vector<int_<0>, int>, meta::vector<int_<1>, float>,
                    meta::vector<int_<2>, double>, meta::vector<int_<3>, bool>>,
                std::is_same<float, back<_>>>::type,
            meta::vector<meta::vector<int_<1>, float>>>);
}

BOOST_AUTO_TEST_SUITE_END()
