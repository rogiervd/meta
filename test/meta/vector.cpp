/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BOOST_TEST_MODULE test_meta_vector
#include "../boost_unit_test.hpp"

#include "meta/vector.hpp"
#include "meta/range.hpp"

typedef meta::vector <> vector0;
typedef meta::vector <int> vector1;
typedef meta::vector <int, bool> vector2;
typedef meta::vector <int, bool, float, double> vector4;

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

#include "meta/transform.hpp"
#include <boost/mpl/placeholders.hpp>

#include "meta/concatenate.hpp"

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_vector)

BOOST_AUTO_TEST_CASE (test_meta_vector) {
    using std::is_same;
    using boost::mpl::equal_to;
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT ((meta::empty <vector0>));
    BOOST_MPL_ASSERT ((meta::empty <meta::back, vector0>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <vector1>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <meta::back, vector2>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <vector4>));

    BOOST_MPL_ASSERT ((equal_to <meta::size <vector0>, mpl::size_t <0> >));
    BOOST_MPL_ASSERT ((equal_to <meta::size <vector1>, mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <meta::size <meta::back, vector1>, mpl::size_t <1> >));
    BOOST_MPL_ASSERT ((equal_to <meta::size <vector4>, mpl::size_t <4> >));

    BOOST_MPL_ASSERT ((is_same <meta::first <vector1>::type, int>));
    BOOST_MPL_ASSERT ((is_same <meta::first <meta::back, vector1>::type, int>));
    BOOST_MPL_ASSERT ((is_same <meta::first <vector2>::type, int>));
    BOOST_MPL_ASSERT ((is_same <meta::first <meta::back, vector2>::type, bool>));
    BOOST_MPL_ASSERT ((is_same <meta::first <vector4>::type, int>));
    BOOST_MPL_ASSERT ((is_same <meta::first <meta::back, vector4>::type, double>));

    BOOST_MPL_ASSERT ((is_same <
        meta::drop <mpl::size_t <0>, vector0>::type,
        vector0>));
    BOOST_MPL_ASSERT ((is_same <
        meta::drop <meta::back, mpl::size_t <0>, vector0>::type,
        vector0>));

    BOOST_MPL_ASSERT ((is_same <
        meta::drop <mpl::size_t <0>, vector1>::type,
        vector1>));
    BOOST_MPL_ASSERT ((is_same <
        meta::drop <meta::back, mpl::size_t <0>, vector1>::type,
        vector1>));

    BOOST_MPL_ASSERT ((is_same <
        meta::drop <mpl::size_t <1>, vector1>::type,
        vector0>));
    BOOST_MPL_ASSERT ((is_same <
        meta::drop <meta::back, mpl::size_t <1>, vector1>::type,
        vector0>));

    BOOST_MPL_ASSERT ((is_same <
        meta::drop <mpl::size_t <2>, vector4>::type,
        meta::vector <float, double> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::drop <meta::back, mpl::size_t <2>, vector4>::type,
        meta::vector <int, bool> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::push <int, vector0>::type,
        meta::vector <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::push <meta::back, int, vector0>::type,
        meta::vector <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::push <bool, vector1>::type,
        meta::vector <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::push <meta::back, bool, vector1>::type,
        meta::vector <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::push <void, vector4>::type,
        meta::vector <void, int, bool, float, double> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::push <meta::back, void, vector4>::type,
        meta::vector <int, bool, float, double, void> >));
}

// Algorithm specialisation for vector

template <typename Type> struct type_wrapper {};

BOOST_AUTO_TEST_CASE (test_meta_transform_vector) {
    using boost::mpl::_1;
    using std::is_same;

    BOOST_MPL_ASSERT ((is_same <
        meta::transform <type_wrapper <_1>, meta::vector<> >::type,
        meta::vector<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::transform <meta::back, type_wrapper <_1>, meta::vector<>
            >::type,
        meta::vector<> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::transform <type_wrapper <_1>,
            meta::vector <int, long, bool> >::type,
        meta::vector <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
    BOOST_MPL_ASSERT ((is_same <
        meta::transform <meta::back, type_wrapper <_1>,
            meta::vector <int, long, bool> >::type,
        meta::vector <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
}

BOOST_AUTO_TEST_CASE (test_meta_concatenate_vector) {
    using std::is_same;

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector<>, meta::vector<> >::type,
        meta::vector<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector <int>, meta::vector<> >::type,
        meta::vector<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector<>, meta::vector <int> >::type,
        meta::vector<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector <int>, meta::vector <bool> >::type,
        meta::vector <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector <int, float>, meta::vector <bool> >::type,
        meta::vector <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <meta::vector <int>, meta::vector <bool, float> >::type,
        meta::vector <int, bool, float> >));
}

BOOST_AUTO_TEST_CASE (test_meta_as_vector) {
    using std::is_same;

    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::list <>>::type,
        meta::vector <>>));
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::list <int>>::type,
        meta::vector <int>>));
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::list <int, float>>::type,
        meta::vector <int, float>>));
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::list <int, float, bool>>::type,
        meta::vector <int, float, bool>>));

    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::list_direction,
            meta::weird_list <int, float>>::type,
        meta::vector <int, float>>));

    // There is a specialisation for meta::vector itself.
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::vector <>>::type,
        meta::vector <>>));
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::vector <int>>::type,
        meta::vector <int>>));
    BOOST_MPL_ASSERT ((is_same <
        meta::as_vector <meta::vector <int, float>>::type,
        meta::vector <int, float>>));
}

BOOST_AUTO_TEST_SUITE_END()

