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

#define BOOST_TEST_MODULE test_meta_enumerate
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/enumerate.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "meta/equal.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_enumerate)

BOOST_AUTO_TEST_CASE (test_meta_enumerate) {
    using boost::mpl::equal_to;
    using std::is_same;
    namespace mpl = boost::mpl;

    typedef meta::enumerate <list0>::type enumerated0;
    typedef meta::enumerate <list4>::type enumerated4;
    typedef meta::enumerate <meta::list_direction, list4>::type
        enumerated4_direction;
    typedef meta::enumerate <meta::list_direction, weird_list4>::type
        weird_enumerated4;

    BOOST_MPL_ASSERT ((meta::empty <enumerated0>));

    BOOST_MPL_ASSERT ((meta::equal <enumerated0, meta::list<> >));
    BOOST_MPL_ASSERT ((meta::equal <enumerated4, meta::list<
            mpl::pair <mpl::size_t <0>, int>,
            mpl::pair <mpl::size_t <1>, bool>,
            mpl::pair <mpl::size_t <2>, float>,
            mpl::pair <mpl::size_t <3>, double>
        > >));

    BOOST_MPL_ASSERT ((is_same <enumerated4, enumerated4_direction>));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction, weird_enumerated4,
        meta::list<
            mpl::pair <mpl::size_t <0>, int>,
            mpl::pair <mpl::size_t <1>, bool>,
            mpl::pair <mpl::size_t <2>, float>,
            mpl::pair <mpl::size_t <3>, double>
        > >));
}

BOOST_AUTO_TEST_SUITE_END()

