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

#define BOOST_TEST_MODULE test_meta_contains
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/contains.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_contains)

BOOST_AUTO_TEST_CASE (test_meta_contains) {
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT_NOT ((meta::contains <int, meta::list<> >));

    BOOST_MPL_ASSERT_NOT ((meta::contains <int, meta::list<float, double> >));
    BOOST_MPL_ASSERT_NOT ((meta::contains <void, meta::list<float, double> >));
    BOOST_MPL_ASSERT ((meta::contains <float, meta::list<float, double> >));
    BOOST_MPL_ASSERT ((meta::contains <double, meta::list<float, double> >));

    BOOST_MPL_ASSERT ((meta::contains <int, list4>));
    BOOST_MPL_ASSERT ((meta::contains <bool, list4>));
    BOOST_MPL_ASSERT ((meta::contains <double, list4>));

    BOOST_MPL_ASSERT_NOT ((meta::contains <meta::list_direction,
            int, meta::weird_list<> >));

    BOOST_MPL_ASSERT_NOT ((meta::contains <meta::list_direction,
        int, meta::weird_list<float, double> >));
    BOOST_MPL_ASSERT_NOT ((meta::contains <meta::list_direction,
        void, meta::weird_list<float, double> >));
    BOOST_MPL_ASSERT ((meta::contains <meta::list_direction,
        float, meta::weird_list<float, double> >));
    BOOST_MPL_ASSERT ((meta::contains <meta::list_direction,
        double, meta::weird_list<float, double> >));

    BOOST_MPL_ASSERT ((meta::contains <meta::list_direction,
        int, weird_list4>));
    BOOST_MPL_ASSERT ((meta::contains <meta::list_direction,
        bool, weird_list4>));
    BOOST_MPL_ASSERT ((meta::contains <meta::list_direction,
        double, weird_list4>));
}

BOOST_AUTO_TEST_SUITE_END()

