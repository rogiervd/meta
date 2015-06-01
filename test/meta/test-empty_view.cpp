/*
Copyright 2013 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_empty_view
#include "../boost_unit_test.hpp"

#include "meta/empty_view.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_empty_view)

BOOST_AUTO_TEST_CASE (test_meta_empty_view) {
    // Specify direction.
    {
        typedef meta::empty_view <meta::list_direction> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::list_direction>));

        BOOST_MPL_ASSERT ((meta::empty <v>));
        BOOST_MPL_ASSERT ((meta::empty <meta::list_direction, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <0>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::list_direction, v>, boost::mpl::size_t <0>>));
    }
    // Don't specify direction: should be "front".
    {
        typedef meta::empty_view <> v;

        BOOST_MPL_ASSERT ((std::is_same <
            meta::default_direction <v>::type, meta::front>));

        BOOST_MPL_ASSERT ((meta::empty <v>));
        BOOST_MPL_ASSERT ((meta::empty <meta::front, v>));

        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <v>, boost::mpl::size_t <0>>));
        BOOST_MPL_ASSERT ((boost::mpl::equal_to <
            meta::size <meta::front, v>, boost::mpl::size_t <0>>));
    }
}

BOOST_AUTO_TEST_SUITE_END()

