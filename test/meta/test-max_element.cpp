/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Meta-programming library for C++.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

