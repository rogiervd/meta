/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

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

#define BOOST_TEST_MODULE test_meta_merge_types
#include "../boost_unit_test.hpp"

#include <type_traits>

#include <boost/mpl/assert.hpp>

#include "meta/merge_types.hpp"

BOOST_AUTO_TEST_SUITE(test_meta_merge_types)

template <typename Type, Type value>
struct constant;

struct degenerate
{
    template <typename Type> struct apply { typedef Type type; };

    template <typename Type> struct apply <Type &>
    {
        typedef Type type;
    };

    template <typename Type> struct apply <Type const>
    {
        typedef Type type;
    };

    template <typename Type, Type value>
        struct apply <constant <Type, value> >
    {
        typedef Type const type;
    };
};

BOOST_AUTO_TEST_CASE (test_meta_generalise) {
    namespace mpl = boost::mpl;
    using std::is_same;
    using meta::generalise;
    using meta::vector;

/*    BOOST_MPL_ASSERT ((is_same <
        generalise <degenerate, constant <long, 7> >::type,
        vector <long, long const, constant <long, 7> >
        >));

    BOOST_MPL_ASSERT ((is_same <
        generalise <degenerate, double const & >::type,
        vector <double, double const, double const &>
        >));

    typedef
        vector <constant <long, 7>, double const &, long, double const, int>
        testcase;

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::generalise_all <degenerate, testcase>::type,
        vector <
            vector <long, long const, constant <long, 7> >,
            vector <double, double const, double const &>,
            vector <long>,
            vector <double, double const>,
            vector <int>
        >
    >));

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::common_start <
            vector <>, vector<>
        >::type,
        vector<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::common_start <
            vector <int>, vector<int>
        >::type,
        vector<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::common_start <
            vector <int, float>, vector<int>
        >::type,
        vector<int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::common_start <
            vector <int, float>, vector<int, double>
        >::type,
        vector<int> >));

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::add_string <
            vector <long, long const, constant <long, 7> >,
            vector <
                vector <double, double const, double const &>,
                vector <double, double const>
            >
        >::type,
        vector <
            vector <long, long const, constant <long, 7> >,
            vector <double, double const, double const &>,
            vector <double, double const>
        >
    >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::add_string <
            vector <long, long const, constant <long, 7> >,
            vector <
                vector <double, double const, double const &>,
                vector <long, long &>,
                vector <double, double const>
            >
        >::type,
        vector <
            vector <long>,
            vector <double, double const, double const &>,
            vector <double, double const>
        >
    >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::add_string <
            vector <long, long const, constant <long, 7> >,
            vector <
                vector <double, double const, double const &>,
                vector <long, long const>,
                vector <double, double const>
            >
        >::type,
        vector <
            vector <long, long const>,
            vector <double, double const, double const &>,
            vector <double, double const>
        >
    >));

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::merge_strings <
            vector <
                vector <double, double const, double const &>,
                vector <long, long const>,
                vector <double, double const>,
                vector <long, long const, constant <long, 7> >
            >
        >::type,
        vector <
            vector <long, long const>,
            vector <double, double const>
        >
    >));

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types_detail::merge_types_to_strings <degenerate,
            vector <
                double const &, long const, double const, constant <long, 7>
            >
        >::type,
        vector <
            vector <long, long const>,
            vector <double, double const>
        >
    >));
*/
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types <degenerate,
            vector <
                double const &, long const, double const, constant <long, 7>
            >
        >::type,
        vector <double const, long const>
    >));

    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types <degenerate,
            vector <
                double const &, long const, double const, constant <long, 7>,
                int, bool, int, bool, int, bool, const int, const bool,
                const int &, float
            >
        >::type,
        vector <double const, long const, int, bool, float>
    >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types <degenerate,
            vector <
                double const &, long const, double const, constant <long, 7>,
                int, bool, int, bool, int, bool, const int, const bool,
                const int &, float, float const
            >
        >::type,
        vector <double const, long const, int, bool, float>
    >));
    BOOST_MPL_ASSERT ((is_same <
        meta::merge_types <degenerate,
            vector <
                double const &, long const, double const, constant <long, 7>,
                int, bool, int, bool, int, bool, const int, const bool,
                const int &, float, float const, constant <bool, true>
            >
        >::type,
        vector <double const, long const, int, bool, float>
    >));
}

BOOST_AUTO_TEST_SUITE_END()

