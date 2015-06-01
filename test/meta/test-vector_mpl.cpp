/*
Copyright 2011, 2012 Rogier van Dalen.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#define BOOST_TEST_MODULE test_meta_vector_mpl
#include "../boost_unit_test.hpp"

#include "meta/vector.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/at.hpp>

#include <boost/mpl/erase.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>

#include <boost/mpl/deref.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>

#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

typedef meta::vector <> vector0;
typedef meta::vector <int> vector1;
typedef meta::vector <int, bool> vector2;
typedef meta::vector <int, bool, float, double> vector4;

BOOST_AUTO_TEST_SUITE(test_meta_vector_mpl)

BOOST_AUTO_TEST_CASE (test_meta_vector_mpl) {
    using namespace boost::mpl;

    BOOST_MPL_ASSERT ((empty <vector0>));
    BOOST_MPL_ASSERT_NOT ((empty <vector1>));
    BOOST_MPL_ASSERT_NOT ((empty <vector4>));

    BOOST_MPL_ASSERT ((equal_to <size <vector0>, int_ <0> >));
    BOOST_MPL_ASSERT ((equal_to <size <vector1>, int_ <1> >));
    BOOST_MPL_ASSERT ((equal_to <size <vector4>, int_ <4> >));

    BOOST_MPL_ASSERT ((std::is_same <front <vector1>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <front <vector4>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <back <vector1>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <back <vector4>::type, double>));

    // The following are not necessarily true for all Front Extensible
    // MPL Sequences but for meta::vector it is a requirement.
    BOOST_MPL_ASSERT ((std::is_same <
        push_front <vector0, long>::type, meta::vector <long> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_front <vector1, long>::type, meta::vector <long, int> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_front <vector2, long>::type, meta::vector <long, int, bool> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_front <vector4, long>::type,
        meta::vector <long, int, bool, float, double> >));

    BOOST_MPL_ASSERT ((std::is_same <
        pop_front <vector1>::type, meta::vector <> >));
    BOOST_MPL_ASSERT ((std::is_same <
        pop_front <vector4>::type, meta::vector <bool, float, double> >));

    BOOST_MPL_ASSERT ((std::is_same <
        push_back <vector0, long>::type, meta::vector <long> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_back <vector1, long>::type, meta::vector <int, long> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_back <vector2, long>::type, meta::vector <int, bool, long> >));
    BOOST_MPL_ASSERT ((std::is_same <
        push_back <vector4, long>::type,
        meta::vector <int, bool, float, double, long> >));

    BOOST_MPL_ASSERT ((std::is_same <
        pop_back <vector1>::type, meta::vector <> >));
    BOOST_MPL_ASSERT ((std::is_same <
        pop_back <vector2>::type, meta::vector <int> >));
    BOOST_MPL_ASSERT ((std::is_same <
        pop_back <vector4>::type, meta::vector <int, bool, float> >));

    BOOST_MPL_ASSERT ((std::is_same <
        at <vector1, int_ <0> >::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector2, int_ <0> >::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector2, int_ <1> >::type, bool>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector4, int_ <0> >::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector4, int_ <1> >::type, bool>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector4, int_ <2> >::type, float>));
    BOOST_MPL_ASSERT ((std::is_same <
        at <vector4, int_ <3> >::type, double>));
}

BOOST_AUTO_TEST_CASE (test_meta_vector_mpl_iterators) {
    using namespace boost::mpl;

    BOOST_MPL_ASSERT ((std::is_same <
        begin <vector0>::type, end <vector0>::type >));

    BOOST_MPL_ASSERT ((std::is_same <
        next <begin <vector1>::type>::type, end <vector1>::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        begin <vector1>::type, prior <end <vector1>::type>::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        next <begin <vector2>::type>::type, prior <end <vector2>::type
            >::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        next <begin <vector4>::type>::type,
        prior <prior <prior <end <vector4>::type>::type>::type>::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        next <next <next <next <begin <vector4>::type>::type>::type>::type
            >::type,
        end <vector4>::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        deref <next <begin <vector4>::type>::type>::type,
        deref <advance <end <vector4>::type, int_ <-3> >::type>::type>));
    BOOST_MPL_ASSERT ((std::is_same <
        deref <advance <begin <vector4>::type, int_ <2> >::type>::type,
        deref <advance <end <vector4>::type, int_ <-2> >::type>::type>));

    BOOST_MPL_ASSERT ((std::is_same <
        deref <begin <vector1>::type>::type, int>));

    BOOST_MPL_ASSERT ((std::is_same <
        deref <begin <vector4>::type>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <
        deref <next <begin <vector4>::type>::type>::type, bool>));
    BOOST_MPL_ASSERT ((std::is_same <
        deref <next <next <begin <vector4>::type>::type>::type>::type,
        float>));
    BOOST_MPL_ASSERT ((std::is_same <
        deref <next <next <next <begin <vector4>::type>::type>::type>::type
            >::type,
        double>));

    BOOST_MPL_ASSERT ((equal_to <
        distance <begin <vector0>::type, end <vector0>::type >::type,
        boost::mpl::size_t <0> >));
    BOOST_MPL_ASSERT ((equal_to <
        distance <begin <vector1>::type, end <vector1>::type >::type,
        boost::mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <
        distance <begin <vector4>::type, end <vector4>::type >::type,
        boost::mpl::size_t <4> >));
    BOOST_MPL_ASSERT ((equal_to <
        distance <next <begin <vector4>::type>::type, end <vector4>::type
            >::type,
        boost::mpl::size_t <3> >));
    BOOST_MPL_ASSERT ((equal_to <
        distance <next <begin <vector4>::type>::type,
            prior <end <vector4>::type>::type >::type,
        boost::mpl::size_t <2> >));
}

BOOST_AUTO_TEST_CASE (test_meta_vector_with_mpl_iterators) {
    using namespace boost::mpl;

    // erase
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector1, begin <vector1>::type>::type,
        vector0
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector2, begin <vector2>::type>::type,
        meta::vector <bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector2, next <begin <vector2>::type>::type>::type,
        vector1
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector4, next <begin <vector4>::type>::type>::type,
        meta::vector <int, float, double>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector4, prior <end <vector4>::type>::type>::type,
        meta::vector <int, bool, float>
        >));

    // erase with range
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector0, begin <vector0>::type, begin <vector0>::type>::type,
        vector0
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector1, begin <vector1>::type, begin <vector1>::type>::type,
        vector1
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector1, begin <vector1>::type, end <vector1>::type>::type,
        vector0
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector2, begin <vector2>::type, begin <vector2>::type>::type,
        vector2
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector2,
            begin <vector2>::type, next <begin <vector2>::type>::type>::type,
        meta::vector <bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector2, begin <vector2>::type, end <vector2>::type>::type,
        vector0
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        erase <vector4, next <begin <vector4>::type>::type,
            prior <end <vector4>::type>::type>::type,
        meta::vector <int, double>
        >));

    // insert
    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector0, begin <vector0>::type, int>::type,
        meta::vector <int>
        >));

    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector1, begin <vector1>::type, bool>::type,
        meta::vector <bool, int>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector1, end <vector1>::type, bool>::type,
        meta::vector <int, bool>
        >));

    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector2, begin <vector2>::type, float>::type,
        meta::vector <float, int, bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector2, next <begin <vector2>::type>::type, float>::type,
        meta::vector <int, float, bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert <vector2, end <vector2>::type, float>::type,
        meta::vector <int, bool, float>
        >));

    // insert_range
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector0, begin <vector0>::type, vector0>::type,
        meta::vector <>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector0, begin <vector0>::type, vector2>::type,
        vector2
        >));

    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector1, begin <vector1>::type, vector0>::type,
        vector1
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector1, begin <vector1>::type, vector2>::type,
        meta::vector <int, bool, int>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector1, end <vector1>::type, vector2>::type,
        meta::vector <int, int, bool>
        >));

    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, begin <vector2>::type, vector0>::type,
        vector2
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, next <begin <vector2>::type>::type, vector0
            >::type,
        vector2
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, end <vector2>::type, vector0>::type,
        vector2
        >));

    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, begin <vector2>::type, vector4>::type,
        meta::vector <int, bool, float, double, int, bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, next <begin <vector2>::type>::type, vector4
            >::type,
        meta::vector <int, int, bool, float, double, bool>
        >));
    BOOST_MPL_ASSERT ((std::is_same <
        insert_range <vector2, end <vector2>::type, vector4>::type,
        meta::vector <int, bool, int, bool, float, double>
        >));
}

template <typename Type> struct wrapped;

template <typename Type> struct wrap
{
    typedef wrapped <Type> type;
};

struct converted;

BOOST_AUTO_TEST_CASE (test_meta_vector_mpl_algorithms) {
    using namespace boost::mpl;

    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector0, wrapped <_>>::type,
        meta::vector <> >));
    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector1, wrapped <_>>::type,
        meta::vector <wrapped <int> > >));
    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector4, wrapped <_>>::type,
        meta::vector <wrapped <int>, wrapped <bool>, wrapped <float>,
            wrapped <double>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector0, wrap <_>>::type,
        meta::vector <> >));
    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector1, wrap <_>>::type,
        meta::vector <wrapped <int> > >));
    BOOST_MPL_ASSERT ((std::is_same <
        transform <vector4, wrap <_>>::type,
        meta::vector <wrapped <int>, wrapped <bool>, wrapped <float>,
            wrapped <double>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        copy_if <vector4, std::is_same <float, _> >::type,
        meta::vector <float> >));

    BOOST_MPL_ASSERT ((std::is_same <
        copy_if <
            meta::vector <
                meta::vector <int_ <0>, int>,
                meta::vector <int_ <1>, float>,
                meta::vector <int_ <2>, double>,
                meta::vector <int_ <3>, bool>
            >,
            std::is_same <float, back <_> >
        >::type,
        meta::vector <meta::vector <int_ <1>, float> > >));
}

BOOST_AUTO_TEST_SUITE_END()

