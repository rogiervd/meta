/*
Copyright 2014, 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE map
#include "../boost_unit_test.hpp"

#include "meta/map.hpp"
#include "meta/range.hpp"

#include <boost/mpl/equal.hpp>
#include "meta/vector.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_map)

using meta::map;
using meta::map_element;

struct int_value;
struct bool_value;

typedef map <> map_0;
typedef map <map_element <int, int_value>> map_1;
typedef map <map_element <bool, bool_value>, map_element <int, int_value>>
    map_2;

BOOST_AUTO_TEST_CASE (test_meta_map) {
    // empty.
    BOOST_MPL_ASSERT ((meta::empty <map_0>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <map_1>));
    BOOST_MPL_ASSERT_NOT ((meta::empty <map_2>));

    // size.
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <map_0>, boost::mpl::size_t <0>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <map_1>, boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal <
        meta::size <map_2>, boost::mpl::size_t <2>>));

    // first.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::first <map_1>::type, map_element <int, int_value>>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::first <map_2>::type, map_element <bool, bool_value>>));

    // drop.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::drop <map_1>::type, map_0>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::drop <map_2>::type, map_1>));

    // push.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::push <map_element <int, int_value>, map_0>::type,
        map_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::push <map_element <bool, bool_value>, map_1>::type,
        map_2>));

    // has_key.
    BOOST_MPL_ASSERT_NOT ((meta::has_key <int, map_0>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <bool, map_0>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, map_0>));

    BOOST_MPL_ASSERT ((meta::has_key <int, map_1>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <bool, map_1>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, map_1>));

    BOOST_MPL_ASSERT ((meta::has_key <int, map_2>));
    BOOST_MPL_ASSERT ((meta::has_key <bool, map_2>));
    BOOST_MPL_ASSERT_NOT ((meta::has_key <long, map_2>));

    // at.
    BOOST_MPL_ASSERT ((std::is_same <meta::at <int, map_1>::type, int_value>));
    BOOST_MPL_ASSERT ((std::is_same <meta::at <int, map_2>::type, int_value>));
    BOOST_MPL_ASSERT ((
        std::is_same <meta::at <bool, map_2>::type, bool_value>));

    // insert: new element.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <int, int_value>, map_0>::type,
        map_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <bool, bool_value>, map_1>::type,
        map_2>));
    // Existing element.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <int, int_value>, map_1>::type,
        map_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <int, int_value>, map_2>::type,
        map <map_element <int, int_value>, map_element <bool, bool_value>>>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <bool, bool_value>, map_2>::type,
        map_2>));
    // Existing element with different value.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <int, short>, map_2>::type,
        map <map_element <int, short>, map_element <bool, bool_value>>>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::insert <map_element <bool, void>, map_2>::type,
        map <map_element <bool, void>, map_element <int, int_value>>>));

    // remove.
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::remove <int, map_1>::type, map_0>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::remove <bool, map_2>::type, map_1>));
    BOOST_MPL_ASSERT ((std::is_same <
        typename meta::remove <int, map_2>::type,
        map <map_element <bool, bool_value>>>));
}

BOOST_AUTO_TEST_SUITE_END()
