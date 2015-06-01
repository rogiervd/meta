/*
Copyright 2011, 2012, 2014 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_transform
#include "../boost_unit_test.hpp"

#include "meta/transform.hpp"
#include "list.hpp"

template <typename Type> struct type_wrapper {};

#include <boost/mpl/placeholders.hpp>
#include "meta/equal.hpp"

namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE(test_meta_transform)

BOOST_AUTO_TEST_CASE (test_meta_transform) {
    using boost::mpl::_;

    BOOST_MPL_ASSERT ((meta::equal <
        meta::transform <type_wrapper <_>, meta::list<> >,
        meta::list<>
        >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>, meta::list<> >,
        meta::list<>
        >));

    BOOST_MPL_ASSERT ((meta::equal <
        meta::transform <type_wrapper <_>,
            meta::list <int, long, bool> >,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>,
            meta::list <int, long, bool> >,
        meta::list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));

    BOOST_MPL_ASSERT ((meta::equal <meta::list_direction,
        meta::transform <type_wrapper <_>,
            meta::weird_list <int, long, bool> >,
        meta::weird_list <
            type_wrapper <int>, type_wrapper <long>, type_wrapper <bool> >
        >));
}

BOOST_AUTO_TEST_SUITE_END()

