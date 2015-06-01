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

#define BOOST_TEST_MODULE test_meta_find
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/find.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_range)

BOOST_AUTO_TEST_CASE (test_meta_find) {
    using std::is_same;
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_floating_point <mpl::_>, meta::list<> >::type,
        meta::list<>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_floating_point <mpl::_>, list4>::type,
        meta::list <float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_pod <mpl::_>, list4>::type,
        list4
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_unsigned <mpl::_>, list4>::type,
        meta::list<bool, float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <std::is_class <mpl::_>, list4>::type,
        meta::list<>
        >));


    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_floating_point <mpl::_>, meta::weird_list<> >::type,
        meta::weird_list<>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_pod <mpl::_>, weird_list4>::type,
        weird_list4
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_unsigned <mpl::_>, weird_list4>::type,
        meta::weird_list<bool, float, double>
        >));

    BOOST_MPL_ASSERT ((is_same <
        meta::find <meta::list_direction,
            std::is_class <mpl::_>, weird_list4>::type,
        meta::weird_list<>
        >));
}

BOOST_AUTO_TEST_SUITE_END()

