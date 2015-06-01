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

#define BOOST_TEST_MODULE test_meta_sort
#include "../boost_unit_test.hpp"

#include "meta/sort.hpp"
#include "list.hpp"

#include <type_traits>
#include "meta/vector.hpp"

#include <boost/mpl/less.hpp>
#include <boost/mpl/greater.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_sort)

BOOST_AUTO_TEST_CASE (test_meta_sort) {
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;
    typedef boost::mpl::less <_1, _2> compare;
    typedef boost::mpl::greater <_1, _2> greater;

    /*
    "sort" sets up a hierarchy of "merges".
    The test for "sort" therefore basically only needs to check whether all
    elements from the original sequence turn up exactly once.
    The order is likely to be correct if "merge" has been tested properly.
    */

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_vector <meta::sort <meta::front,
            meta::vector <>>::type>::type,
        meta::vector<>>));

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_vector <meta::sort <meta::front, compare,
            meta::vector <mpl::int_ <2>>>::type>::type,
        meta::vector<mpl::int_ <2>>>));

    // Result
    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_vector <meta::sort <
            meta::vector <mpl::int_ <2>, mpl::int_ <3>>>::type>::type,
        meta::vector<mpl::int_ <2>, mpl::int_ <3>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_list <meta::sort <meta::list_direction, compare,
            meta::list <mpl::int_ <3>, mpl::int_ <2>>>::type>::type,
        meta::list <mpl::int_ <2>, mpl::int_ <3>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_vector <meta::sort <greater,
            meta::vector <mpl::int_ <3>, mpl::int_ <2>, mpl::int_ <7>>>::type
            >::type,
        meta::vector<mpl::int_ <7>, mpl::int_ <3>, mpl::int_ <2>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_list <meta::sort <meta::list_direction, greater,
            meta::list <mpl::int_ <3>, mpl::int_ <2>,
                mpl::int_ <7>, mpl::int_ <-1>>>::type>::type,
        meta::list <mpl::int_ <7>, mpl::int_ <3>,
            mpl::int_ <2>, mpl::int_ <-1>>>));

    BOOST_MPL_ASSERT ((std::is_same <
        meta::as_vector <meta::sort <meta::front, compare,
            meta::vector <mpl::int_ <3>, mpl::int_ <2>,
                mpl::int_ <7>, mpl::int_ <-1>, mpl::int_ <-3>,
                mpl::int_ <4>, mpl::int_ <27>>>::type>::type,
        meta::vector<mpl::int_ <-3>, mpl::int_ <-1>, mpl::int_ <2>,
            mpl::int_ <3>, mpl::int_ <4>, mpl::int_ <7>, mpl::int_ <27>>>));
}

BOOST_AUTO_TEST_SUITE_END()

