/*
Copyright 2013, 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_any
#include "../boost_unit_test.hpp"

#include "meta/any_of.hpp"

#include <boost/mpl/bool.hpp>
#include "list.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_any_of)

BOOST_AUTO_TEST_CASE (test_meta_any_of) {
    namespace mpl = boost::mpl;

    static_assert (!meta::any_of <meta::list<>>::value, "");

    static_assert (!meta::any_of <meta::list <mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::list <mpl::true_>>::value, "");

    static_assert (!meta::any_of <
        meta::list <mpl::false_, mpl::false_>>::value, "");
    static_assert (meta::any_of <
        meta::list <mpl::false_, mpl::true_>>::value, "");
    static_assert (meta::any_of <
        meta::list <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::any_of <
        meta::list <mpl::true_, mpl::true_>>::value, "");

    // Short-circuit.
    static_assert (meta::any_of <meta::list <mpl::true_, int>>::value, "");
    static_assert (meta::any_of <
        meta::list <mpl::true_, int, bool>>::value, "");

    // weird_list
    static_assert (!
        meta::any_of <meta::list_direction, meta::weird_list<>>::value, "");

    static_assert (!meta::any_of <meta::list_direction,
        meta::weird_list <mpl::false_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::list_direction,
        meta::weird_list <mpl::false_, mpl::true_>>::value, "");
    static_assert (meta::any_of <meta::list_direction,
        meta::weird_list <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::list_direction,
        meta::weird_list <mpl::true_, mpl::true_>>::value, "");
}

// Without including meta/vector.hpp!
// This should just use the type.
BOOST_AUTO_TEST_CASE (test_meta_any_of_vector) {
    static_assert (!meta::any_of <meta::vector<>>::value, "");

    static_assert (!meta::any_of <meta::vector <mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::vector <mpl::true_>>::value, "");

    static_assert (!meta::any_of <
        meta::vector <mpl::false_, mpl::false_>>::value, "");
    static_assert (meta::any_of <
        meta::vector <mpl::false_, mpl::true_>>::value, "");
    static_assert (meta::any_of <
        meta::vector <mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::any_of <
        meta::vector <mpl::true_, mpl::true_>>::value, "");

    static_assert (!meta::any_of <meta::vector <
        mpl::false_, mpl::false_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::false_, mpl::false_, mpl::true_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::false_, mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::false_, mpl::true_, mpl::true_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::true_, mpl::false_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::true_, mpl::false_, mpl::true_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::true_, mpl::true_, mpl::false_>>::value, "");
    static_assert (meta::any_of <meta::vector <
        mpl::true_, mpl::true_, mpl::true_>>::value, "");

    // Short-circuit.
    static_assert (meta::any_of <
        meta::vector <mpl::true_, int>>::value, "");
    static_assert (meta::any_of <
        meta::vector <mpl::true_, int, bool>>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
