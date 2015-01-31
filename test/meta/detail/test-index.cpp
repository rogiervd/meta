/*
Copyright 2015 Rogier van Dalen.

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

#define BOOST_TEST_MODULE test_meta_index
#include "../../boost_unit_test.hpp"

#include "meta/detail/index.hpp"

#include <type_traits>

template <class Key> struct key_entry {
    typedef Key key;
};

template <class Key, class Value> struct key_value {
    typedef Key key;
    typedef Value value;
};

BOOST_AUTO_TEST_SUITE(test_meta_index)

BOOST_AUTO_TEST_CASE (test_meta_index_contains) {
    using meta::index_detail::index;
    using meta::index_detail::contains;

    {
        typedef index<> i;

        static_assert (!contains <void, i>::value, "");
        static_assert (!contains <int, i>::value, "");
        static_assert (!contains <float, i>::value, "");
    }
    {
        typedef index <key_entry <int>> i;

        static_assert (!contains <void, i>::value, "");
        static_assert (contains <int, i>::value, "");
        static_assert (!contains <float, i>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>> i;

        static_assert (!contains <void, i>::value, "");
        static_assert (contains <int, i>::value, "");
        static_assert (!contains <float, i>::value, "");
        static_assert (contains <double, i>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>,
            key_entry <void>, key_entry <short>> i;

        static_assert (contains <void, i>::value, "");
        static_assert (contains <int, i>::value, "");
        static_assert (!contains <float, i>::value, "");
        static_assert (contains <double, i>::value, "");
        static_assert (contains <short, i>::value, "");
    }
    // This fails because it contains key "int" twice.
    /*{
        typedef index <key_entry <int>, key_entry <double>, key_entry <int>> i;

        i();
    }*/
}

BOOST_AUTO_TEST_CASE (test_meta_index_remove) {
    using meta::index_detail::index;
    using meta::index_detail::remove;

    {
        typedef index <key_entry <int>> i;

        static_assert (std::is_same <remove <int, i>::type,
            index<>>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>> i;

        static_assert (std::is_same <remove <int, i>::type,
            index <key_entry <double>>>::value, "");
        static_assert (std::is_same <remove <double, i>::type,
            index <key_entry <int>>>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>,
            key_entry <void>, key_entry <short>> i;

        static_assert (std::is_same <remove <int, i>::type,
            index <key_entry <double>, key_entry <void>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <remove <double, i>::type,
            index <key_entry <int>, key_entry <void>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <remove <void, i>::type,
            index <key_entry <int>, key_entry <double>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <remove <short, i>::type,
            index <key_entry <int>, key_entry <double>, key_entry <void>>
            >::value, "");
    }
}

BOOST_AUTO_TEST_CASE (test_meta_index_insert) {
    using meta::index_detail::index;
    using meta::index_detail::insert;

    // Not yet in the index: push_front.
    {
        typedef index <> i;

        static_assert (std::is_same <insert <key_value <int, bool>, i>::type,
            index <key_value <int, bool>>>::value, "");
    }
    {
        typedef index <key_entry <bool>, key_entry <void>> i;

        static_assert (std::is_same <insert <key_value <int, bool>, i>::type,
            index <key_value <int, bool>, key_entry <bool>, key_entry <void>>
            >::value, "");
    }

    // Already in the index: remove and push_front.
    {
        typedef index <key_entry <int>> i;

        static_assert (std::is_same <insert <key_value <int, bool>, i>::type,
            index <key_value <int, bool>>>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>> i;

        static_assert (std::is_same <insert <key_value <int, void>, i>::type,
            index <key_value <int, void>, key_entry <double>>>::value, "");
        static_assert (std::is_same <insert <key_value <double, void>, i>::type,
            index <key_value <double, void>, key_entry <int>>>::value, "");
    }
    {
        typedef index <key_entry <int>, key_entry <double>,
            key_entry <void>, key_entry <short>> i;

        static_assert (std::is_same <insert <key_value <int, char>, i>::type,
            index <key_value <int, char>,
                key_entry <double>, key_entry <void>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <insert <key_value <double, char>, i>::type,
            index <key_value <double, char>,
                key_entry <int>, key_entry <void>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <insert <key_value <void, char>, i>::type,
            index <key_value <void, char>,
                key_entry <int>, key_entry <double>, key_entry <short>>
            >::value, "");
        static_assert (std::is_same <insert <key_value <short, char>, i>::type,
            index <key_value <short, char>,
                key_entry <int>, key_entry <double>, key_entry <void>>
            >::value, "");
    }
}

BOOST_AUTO_TEST_SUITE_END()
