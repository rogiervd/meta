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

#define BOOST_TEST_MODULE test_meta_flatten
#include "../boost_unit_test.hpp"

#include <type_traits>

#include "list.hpp"
#include "meta/flatten.hpp"
#include "meta/mpl.hpp"

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_flatten)

// \todo weird_list?
BOOST_AUTO_TEST_CASE (test_meta_flatten) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using meta::list;

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <> >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<> > >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<>, list<> > >::type,
        meta::list <> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list <int>, list<> > >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list<>, list <int> > >::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <list <list <bool>, list <int> > >::type,
        meta::list <bool, int> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<>, list <int>, list <float, bool>, list <double> >
            >::type,
        meta::list <int, float, bool, double> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<int, float>, list <>, list <bool>, list <double> >
            >::type,
        meta::list <int, float, bool, double> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::flatten <
            list <list<int, float>, list <bool>, list <bool, float>,
                list <double> >
            >::type,
        meta::list <int, float, bool, bool, float, double> >));
}

BOOST_AUTO_TEST_SUITE_END()

