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

/**
Merge duplicate types (according to a stack of criteria) in a type sequence.
*/

#ifndef META_MERGE_TYPES_HPP_INCLUDED
#define META_MERGE_TYPES_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/transform.hpp"
#include "meta/fold.hpp"

#include "meta/vector.hpp"

namespace meta {

template <typename Degenerate, typename Type> struct generalise;

namespace merge_types_detail {

    // generalise
    template <typename Degenerate, typename Type,
        typename Generalisation = typename mpl::apply <Degenerate, Type>::type>
    struct generalise_impl
    : meta::push <meta::back, Type,
        typename generalise_impl <Degenerate, Generalisation>::type> {};

    // Type is the same as its degenerate version
    template <typename Degenerate, typename Type>
        struct generalise_impl <Degenerate, Type, Type>
    { typedef meta::vector <Type> type; };

    /**
    Return a vector with the elements that String1 and String2 both begin with.
    */
    template <typename String1, typename String2> struct common_start
    { typedef vector<> type; };

    template <typename Matching, typename ... Rest1, typename ... Rest2>
        struct common_start <
            vector <Matching, Rest1 ...>, vector <Matching, Rest2 ...> >
    : meta::push <meta::front, Matching, typename
        common_start <vector <Rest1 ...>, vector <Rest2 ...> >::type> {};

    template <typename String, typename Strings,
        typename IrrelevantStrings = vector<> >
    struct add_string;

    // No match
    template <typename String, typename First, typename ... Rest,
        typename ... IrrelevantStrings>
    struct add_string <String, vector <First, Rest ...>,
        vector <IrrelevantStrings ...> >
    : add_string <String,
        vector <Rest ...>,
        vector <IrrelevantStrings ..., First>
    > {};

    // Finished looking
    template <typename String, typename IrrelevantStrings>
    struct add_string <String, vector<>, IrrelevantStrings>
    : meta::push <meta::front, String, IrrelevantStrings> {};

    // First string matches.
    template <typename MatchingType, typename ... Rest,
        typename ... MatchingRest, typename ... OtherStrings,
        typename ... IrrelevantStrings>
    struct add_string <
        vector <MatchingType, Rest ...>,
        vector <vector <MatchingType, MatchingRest ...>, OtherStrings ...>,
        vector <IrrelevantStrings ...> >
    {
        typedef typename common_start <
                vector <MatchingType, Rest ...>,
                vector <MatchingType, MatchingRest ...>
            >::type new_string;

        typedef vector <new_string, IrrelevantStrings ..., OtherStrings ...>
            type;
    };

    template <typename Strings>
        struct merge_strings
    : meta::fold <meta::front, add_string <mpl::_2, mpl::_1>,
        vector<>, Strings> {};

    template <typename Degenerate, typename Type, typename Strings>
    struct add_type
    : add_string <typename generalise <Degenerate, Type>::type, Strings> {};

    template <typename Degenerate, typename Types>
        struct merge_types_to_strings
    : meta::fold <meta::back, add_type <Degenerate, mpl::_2, mpl::_1>,
        vector<>, Types> {};

} // namespace merge_types_detail

template <typename Degenerate, typename Type> struct generalise
: merge_types_detail::generalise_impl <Degenerate, Type> {};

template <typename Degenerate, typename Types>
    struct merge_types
{
    typedef typename merge_types_detail::merge_types_to_strings <
        Degenerate, Types>::type strings;
    typedef typename transform <meta::first <meta::back, mpl::_>, strings>::type
        type;
};

} // namespace meta

#endif // META_MERGE_TYPES_HPP_INCLUDED

