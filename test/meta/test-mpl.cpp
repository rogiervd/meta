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

#define BOOST_TEST_MODULE test_meta_mpl
#include "../boost_unit_test.hpp"

#include "meta/mpl.hpp"

#include <type_traits>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal_to.hpp>

#include "meta/fold.hpp"

#include "meta/equal.hpp"
#include "meta/vector.hpp"

namespace mpl = boost::mpl;

typedef mpl::vector <> vector0;
typedef mpl::vector <int> vector1;
typedef mpl::vector <int, bool> vector2;
typedef mpl::vector <int, bool, float, double> vector4;

BOOST_AUTO_TEST_SUITE(test_meta_mpl)

BOOST_AUTO_TEST_CASE (test_meta_mpl_intrinsic) {
    // empty
    BOOST_MPL_ASSERT ((meta::empty <vector0>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <vector1>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <vector4>));

    BOOST_MPL_ASSERT ((meta::empty <meta::back, vector0>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <meta::back, vector4>));

    // size
    BOOST_MPL_ASSERT ((mpl::equal_to <meta::size <vector0>, mpl::int_ <0> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <meta::size <vector1>, mpl::int_ <1> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <meta::size <vector4>, mpl::int_ <4> >));

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::size <meta::back, vector0>, mpl::int_ <0> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::size <meta::back, vector4>, mpl::int_ <4> >));

    // first
    BOOST_MPL_ASSERT ((std::is_same <meta::first <vector1>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <meta::first <vector2>::type, int>));
    BOOST_MPL_ASSERT ((std::is_same <meta::first <vector4>::type, int>));

    BOOST_MPL_ASSERT ((std::is_same <meta::first <meta::back, vector1>::type,
        int>));
    BOOST_MPL_ASSERT ((std::is_same <meta::first <meta::back, vector2>::type,
        bool>));
    BOOST_MPL_ASSERT ((std::is_same <meta::first <meta::back, vector4>::type,
        double>));

    // drop
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <vector1>::type, vector0>));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <vector2>::type, mpl::vector <bool> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <vector4>::type, mpl::vector <bool, float, double> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <meta::back, vector1>::type,
        mpl::vector <> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <meta::back, vector2>::type,
        mpl::vector <int> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <meta::back, vector4>::type,
        mpl::vector <int, bool, float> >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <mpl::int_<2>, vector2>::type, mpl::vector<> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <mpl::int_<2>, vector4>::type,
        mpl::vector <float, double>>));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <meta::back, mpl::int_<2>, vector2>::type,
        mpl::vector<> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::drop <meta::back, mpl::int_<2>, vector4>::type,
        mpl::vector <int, bool> >));

    // push
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <int, vector0>::type, mpl::vector <int> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <long, vector1>::type, mpl::vector <long, int> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <long, vector2>::type, mpl::vector <long, int, bool> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <long, vector4>::type,
        mpl::vector <long, int, bool, float, double> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <meta::back, long, vector0>::type,
        mpl::vector <long> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <meta::back, long, vector1>::type,
        mpl::vector <int, long> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <meta::back, long, vector2>::type,
        mpl::vector <int, bool, long> >));
    BOOST_MPL_ASSERT ((meta::equal <
        meta::push <meta::back, long, vector4>::type,
        mpl::vector <int, bool, float, double, long> >));

    // fold
    BOOST_MPL_ASSERT ((std::is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::vector<>,
            mpl::vector <int, bool>
        >::type,
        meta::vector <bool, int> >));
    BOOST_MPL_ASSERT ((std::is_same <
        meta::fold <meta::back, meta::push <mpl::_2, mpl::_1>, meta::vector<>,
            mpl::vector <int, bool>
        >::type,
        meta::vector <int, bool> >));
    BOOST_MPL_ASSERT ((std::is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::vector<>,
            mpl::vector <>
        >::type,
        meta::vector <> >));
    BOOST_MPL_ASSERT ((std::is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::vector<int>,
            mpl::vector <>
        >::type,
        meta::vector <int> >));
    BOOST_MPL_ASSERT ((std::is_same <
        meta::fold <meta::push <mpl::_2, mpl::_1>, meta::vector<int>,
            mpl::vector <bool>
        >::type,
        meta::vector <bool, int> >));
}

BOOST_AUTO_TEST_SUITE_END()

