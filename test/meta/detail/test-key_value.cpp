/*
Copyright 2013 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_lookup
#include "../../boost_unit_test.hpp"

#include "meta/detail/key_value.hpp"

#include <type_traits>

#include <boost/mpl/pair.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>

#include "meta/vector.hpp"
#include "meta/transform.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_lookup)

namespace mpl = boost::mpl;

template <class Type> struct value_wrapper;

BOOST_AUTO_TEST_CASE (test_meta_lookup) {
    typedef meta::vector <int, bool, long> types;

    typedef meta::transform <mpl::pair <mpl::_1, value_wrapper <mpl::_1>>,
        types> key_value_pairs;

    typedef meta::key_value_detail::make_index <key_value_pairs>::type
        index;

    // Test contains.
    BOOST_MPL_ASSERT ((meta::key_value_detail::contains <int, index>));
    BOOST_MPL_ASSERT ((meta::key_value_detail::contains <long, index>));
    BOOST_MPL_ASSERT ((meta::key_value_detail::contains <bool, index>));
    BOOST_MPL_ASSERT_NOT ((meta::key_value_detail::contains <char, index>));

    // Test value.
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value <int, index>::type,
            value_wrapper <int>>));
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value <long, index>::type,
            value_wrapper <long>>));
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value <bool, index>::type,
            value_wrapper <bool>>));

    // Test value_or.
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value_or <int, void, index>::type,
            value_wrapper <int>>));
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value_or <long, void, index>::type,
            value_wrapper <long>>));
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value_or <bool, void, index>::type,
            value_wrapper <bool>>));
    // Not in index.
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value_or <char, void, index>::type, void>));
    BOOST_MPL_ASSERT ((std::is_same <
            meta::key_value_detail::value_or <char, int, index>::type, int>));

    // Test remove.
    {
        typedef meta::key_value_detail::remove <int, index>::type
            index_without_int;

        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <int, index_without_int>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <long, index_without_int>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <bool, index_without_int>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <char, index_without_int>));

        typedef meta::key_value_detail::remove <long, index>::type
            index_without_long;

        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <int, index_without_long>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <long, index_without_long>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <bool, index_without_long>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <char, index_without_long>));

        typedef meta::key_value_detail::remove <bool, index>::type
            index_without_bool;

        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <int, index_without_bool>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <long, index_without_bool>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <bool, index_without_bool>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <char, index_without_bool>));
    }

    // Test insert.
    {
        typedef meta::key_value_detail::insert <
                short, value_wrapper <short>, index>::type
            index_with_short;

        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <int, index_with_short>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <long, index_with_short>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <bool, index_with_short>));
        BOOST_MPL_ASSERT ((
            meta::key_value_detail::contains <long, index_with_short>));
        BOOST_MPL_ASSERT_NOT ((
            meta::key_value_detail::contains <char, index_with_short>));

        BOOST_MPL_ASSERT ((std::is_same <
                meta::key_value_detail::value <short, index_with_short>::type,
                value_wrapper <short>>));
    }
}

BOOST_AUTO_TEST_SUITE_END()
