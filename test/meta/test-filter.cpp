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

#define BOOST_TEST_MODULE test_meta_range
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/filter.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "meta/equal.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_filter)

BOOST_AUTO_TEST_CASE (test_meta_filter) {
    namespace mpl = boost::mpl;

    BOOST_MPL_ASSERT ((meta::equal <
        meta::filter <std::is_floating_point <mpl::_>, meta::list<>>,
        meta::list<>
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::filter <std::is_floating_point <mpl::_>, list4>::type,
        meta::list <float, double>
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::filter <std::is_pod <mpl::_>, list4>,
        list4
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::filter <std::is_unsigned <mpl::_>, list4>,
        meta::list<bool>
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::filter <std::is_class <mpl::_>, list4>,
        meta::list<>
        >));


    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::filter <std::is_floating_point <mpl::_>, meta::weird_list<>>,
        meta::weird_list<>
        >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::filter <std::is_floating_point <mpl::_>, weird_list4>,
        meta::weird_list <float, double>
        >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::filter <std::is_class <mpl::_>, weird_list4>,
        meta::weird_list<>
        >));

}

BOOST_AUTO_TEST_SUITE_END()

