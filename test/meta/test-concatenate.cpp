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

#define BOOST_TEST_MODULE test_meta_concatenate
#include "../boost_unit_test.hpp"

#include <type_traits>
#include "list.hpp"
#include "meta/concatenate.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_concatenate)

BOOST_AUTO_TEST_CASE (test_meta_concatenate) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using meta::list;
    using meta::weird_list;
    typedef meta::list_direction direction;

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list<>, list<> >::type,
        list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list<> >::type,
        list<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list<>, list <int> >::type,
        list<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list <bool> >::type,
        list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int, float>, list <bool> >::type,
        list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <list <int>, list <bool, float> >::type,
        list <int, bool, float> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int>, list<> >::type,
        list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list<>, list <int> >::type,
        list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int>, list <bool> >::type,
        list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int, float>, list <bool> >::type,
        list <int, float, bool> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int>, weird_list<> >::type,
        weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list<>, weird_list <int> >::type,
        weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int>, weird_list <bool>
            >::type,
        weird_list <int, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int, float>, weird_list <bool>
            >::type,
        weird_list <int, float, bool> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <weird_list <int, float>, list <bool> >::type,
        list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, list <int, float>, weird_list <bool>
            >::type,
        weird_list <int, float, bool> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::concatenate <direction, weird_list <int, float>, list <bool>
            >::type,
        list <int, float, bool> >));
}

BOOST_AUTO_TEST_SUITE_END()

