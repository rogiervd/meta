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

#define BOOST_TEST_MODULE test_meta_take
#include "../boost_unit_test.hpp"

#include "meta/take.hpp"

#include <type_traits>

#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_take)

BOOST_AUTO_TEST_CASE (test_meta_take) {
    namespace mpl = boost::mpl;

    {
        typedef meta::take <mpl::int_ <0>, meta::list<>> empty_list;
        BOOST_MPL_ASSERT ((meta::empty <empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <empty_list>, mpl::size_t <0>>));
    }

    {
        typedef meta::take <mpl::int_ <0>, meta::list <int>> empty_list;
        BOOST_MPL_ASSERT ((meta::empty <empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <empty_list>, mpl::size_t <0>>));
    }

    {
        typedef meta::take <mpl::int_ <1>, meta::list<>> empty_list;
        BOOST_MPL_ASSERT ((meta::empty <empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <empty_list>, mpl::size_t <0>>));
    }

    {
        typedef meta::take <mpl::int_ <1>, meta::list <int>> list;

        BOOST_MPL_ASSERT_NOT ((meta::empty <list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <meta::size <list>, mpl::size_t <1>>));
        BOOST_MPL_ASSERT ((std::is_same <meta::first <list>::type, int>));

        typedef meta::drop <list>::type empty_list;
        BOOST_MPL_ASSERT ((meta::empty <empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <empty_list>, mpl::size_t <0>>));
    }

    // Limit less than length of list.
    {
        typedef meta::take <meta::list_direction,
            mpl::int_ <2>, meta::weird_list <int, double, bool>> list;

        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::list_direction, list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction,list>, mpl::size_t <2>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::list_direction, list>::type, int>));

        typedef meta::drop <meta::list_direction, list>::type list_1;
        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::list_direction, list_1>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction, list_1>, mpl::size_t <1>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::list_direction, list_1>::type, double>));

        typedef meta::drop <meta::list_direction, list_1>::type empty_list;
        BOOST_MPL_ASSERT ((meta::empty <meta::list_direction, empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction, empty_list>, mpl::size_t <0>>));

        typedef meta::drop <meta::list_direction, mpl::size_t <2>, list>::type
            empty_list_2;
        BOOST_MPL_ASSERT ((std::is_same <empty_list, empty_list_2>));
    }

    // Limit greater than length of list.
    {
        typedef meta::take <meta::list_direction,
            mpl::int_ <3>, meta::weird_list <int, double>> list;

        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::list_direction, list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction,list>, mpl::size_t <2>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::list_direction, list>::type, int>));

        typedef meta::drop <meta::list_direction, list>::type list_1;
        BOOST_MPL_ASSERT_NOT ((meta::empty <meta::list_direction, list_1>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction, list_1>, mpl::size_t <1>>));
        BOOST_MPL_ASSERT ((std::is_same <
            meta::first <meta::list_direction, list_1>::type, double>));

        typedef meta::drop <meta::list_direction, list_1>::type empty_list;
        BOOST_MPL_ASSERT ((meta::empty <meta::list_direction, empty_list>));
        BOOST_MPL_ASSERT ((mpl::equal_to <
            meta::size <meta::list_direction, empty_list>, mpl::size_t <0>>));

        typedef meta::drop <meta::list_direction, mpl::size_t <2>, list>::type
            empty_list_2;
        BOOST_MPL_ASSERT ((std::is_same <empty_list, empty_list_2>));
    }
}

BOOST_AUTO_TEST_SUITE_END()

