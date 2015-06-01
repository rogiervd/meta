/*
Copyright 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_any_of_c
#include "../boost_unit_test.hpp"

#include "meta/any_of_c.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_any_of_c)

BOOST_AUTO_TEST_CASE (test_meta_any_of_c) {

    static_assert (!meta::any_of_c<>::value, "");

    static_assert (!meta::any_of_c <false>::value, "");
    static_assert (meta::any_of_c <true>::value, "");

    static_assert (!meta::any_of_c <false, false>::value, "");
    static_assert (meta::any_of_c <false, true>::value, "");
    static_assert (meta::any_of_c <true, false>::value, "");
    static_assert (meta::any_of_c <true, true>::value, "");

    static_assert (!meta::any_of_c <false, false, false>::value, "");
    static_assert (meta::any_of_c <false, false, true>::value, "");
    static_assert (meta::any_of_c <false, true, false>::value, "");
    static_assert (meta::any_of_c <false, true, true>::value, "");
    static_assert (meta::any_of_c <true, false, false>::value, "");
    static_assert (meta::any_of_c <true, false, true>::value, "");
    static_assert (meta::any_of_c <true, true, false>::value, "");
    static_assert (meta::any_of_c <true, true, true>::value, "");

    static_assert (!meta::any_of_c <false, false, false, false>::value, "");
    static_assert (meta::any_of_c <false, false, false, true>::value, "");
    static_assert (meta::any_of_c <false, false, true, false>::value, "");
    static_assert (meta::any_of_c <false, false, true, true>::value, "");
    static_assert (meta::any_of_c <false, true, false, false>::value, "");
    static_assert (meta::any_of_c <false, true, false, true>::value, "");
    static_assert (meta::any_of_c <false, true, true, false>::value, "");
    static_assert (meta::any_of_c <false, true, true, true>::value, "");
    static_assert (meta::any_of_c <true, false, false, false>::value, "");
    static_assert (meta::any_of_c <true, false, false, true>::value, "");
    static_assert (meta::any_of_c <true, false, true, false>::value, "");
    static_assert (meta::any_of_c <true, false, true, true>::value, "");
    static_assert (meta::any_of_c <true, true, false, false>::value, "");
    static_assert (meta::any_of_c <true, true, false, true>::value, "");
    static_assert (meta::any_of_c <true, true, true, false>::value, "");
    static_assert (meta::any_of_c <true, true, true, true>::value, "");

    static_assert (!meta::any_of_c <
        false, false, false, false, false>::value, "");
    static_assert (meta::any_of_c <
        false, false, false, false, true>::value, "");
    static_assert (meta::any_of_c <
        false, false, false, true, false>::value, "");
    static_assert (meta::any_of_c <
        false, false, false, true, true>::value, "");
    static_assert (meta::any_of_c <
        false, false, true, false, false>::value, "");
    static_assert (meta::any_of_c <
        false, false, true, false, true>::value, "");
    static_assert (meta::any_of_c <
        false, false, true, true, false>::value, "");
    static_assert (meta::any_of_c <
        false, false, true, true, true>::value, "");
    static_assert (meta::any_of_c <
        false, true, false, false, false>::value, "");
    static_assert (meta::any_of_c <
        false, true, false, false, true>::value, "");
    static_assert (meta::any_of_c <
        false, true, false, true, false>::value, "");
    static_assert (meta::any_of_c <
        false, true, false, true, true>::value, "");
    static_assert (meta::any_of_c <
        false, true, true, false, false>::value, "");
    static_assert (meta::any_of_c <
        false, true, true, false, true>::value, "");
    static_assert (meta::any_of_c <
        false, true, true, true, false>::value, "");
    static_assert (meta::any_of_c <
        false, true, true, true, true>::value, "");
    static_assert (meta::any_of_c <
        true, false, false, false, false>::value, "");
    static_assert (meta::any_of_c <
        true, false, false, false, true>::value, "");
    static_assert (meta::any_of_c <
        true, false, false, true, false>::value, "");
    static_assert (meta::any_of_c <
        true, false, false, true, true>::value, "");
    static_assert (meta::any_of_c <
        true, false, true, false, false>::value, "");
    static_assert (meta::any_of_c <
        true, false, true, false, true>::value, "");
    static_assert (meta::any_of_c <
        true, false, true, true, false>::value, "");
    static_assert (meta::any_of_c <
        true, false, true, true, true>::value, "");
    static_assert (meta::any_of_c <
        true, true, false, false, false>::value, "");
    static_assert (meta::any_of_c <
        true, true, false, false, true>::value, "");
    static_assert (meta::any_of_c <
        true, true, false, true, false>::value, "");
    static_assert (meta::any_of_c <
        true, true, false, true, true>::value, "");
    static_assert (meta::any_of_c <
        true, true, true, false, false>::value, "");
    static_assert (meta::any_of_c <
        true, true, true, false, true>::value, "");
    static_assert (meta::any_of_c <
        true, true, true, true, false>::value, "");
    static_assert (meta::any_of_c <
        true, true, true, true, true>::value, "");
}

BOOST_AUTO_TEST_SUITE_END()
