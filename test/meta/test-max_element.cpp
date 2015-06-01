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

#define BOOST_TEST_MODULE test_meta_max_element
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/max_element.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_max_element)

BOOST_AUTO_TEST_CASE (test_meta_max_element) {
    namespace mpl = boost::mpl;
    using mpl::int_;
    using meta::list;

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <list <int_ <4> > >::type,
        int_ <4> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <list <int_ <4>, int_ <5> > >::type,
        int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <list <int_ <5>, int_ <4> > >::type,
        int_ <5> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <list <int_ <5>, int_ <4>, int_ <7> > >::type,
        int_ <7> >));

    // Use std::integral_constant
    static_assert (
        meta::max_element <list <
            std::integral_constant <int, 5>,
            std::integral_constant <int, 4>,
            std::integral_constant <int, 7> > >::type::value == 7, "");

    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <meta::list_direction,
            list <int_ <5>, int_ <4>, int_ <7> > >::type,
        int_ <7> >));
    BOOST_MPL_ASSERT ((mpl::equal_to <
        meta::max_element <meta::list_direction,
            meta::weird_list <int_ <5>, int_ <4>, int_ <7> > >::type,
        int_ <7> >));
}

BOOST_AUTO_TEST_SUITE_END()

