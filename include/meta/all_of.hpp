/*
Copyright 2013, 2015 Rogier van Dalen.

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

#ifndef META_ALL_OF_HPP_INCLUDED
#define META_ALL_OF_HPP_INCLUDED

#include <boost/mpl/if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Return true iff all elements in Range are true.
    If Range is empty, also return true.
    Direction can be left out.
    */
    template <typename Direction, typename Range = void> struct all_of;

    template <typename Range> struct all_of <Range>
    : all_of <typename default_direction <Range>::type, Range> {};

    namespace implementation {
        template <typename Direction, typename Range> struct all_of_non_empty
        : mpl::if_ <typename first <Direction, Range>::type,
            meta::all_of <Direction, typename drop <Direction, Range>::type>,
            mpl::false_>::type {};
    } // namespace implementation

    template <typename Direction, typename Range> struct all_of
    : mpl::if_ <empty <Direction, Range>,
        mpl::true_, implementation::all_of_non_empty <Direction, Range>>::type
    {};

    /*
    Specialisation for vector.
    In profiling template instantiations in a real project, this turned out a
    bottleneck.
    If the first type is false, then the rest should not be evaluated.
    It is therefore not possible to get this below O(n) instantiations.
    */
    namespace implementation {

        template <bool first, class ... Types> struct all_of_vector;

        template <class ... Types> struct all_of_vector <false, Types ...>
        : boost::mpl::false_ {};

        template <> struct all_of_vector <true>
        : boost::mpl::true_ {};

        template <class Next, class ... Types>
            struct all_of_vector <true, Next, Types ...>
        : all_of_vector <Next::value, Types...> {};

    } // namespace implementation

    // Without direction.

    template <> struct all_of <vector<>> : mpl::true_ {};

    template <class Type1> struct all_of <vector <Type1>> : Type1 {};

    template <class Type1, class ... Types>
        struct all_of <vector <Type1, Types ...>>
    : implementation::all_of_vector <Type1::value, Types ...> {};

    // With direction.

    template <> struct all_of <front, vector<>> : mpl::true_ {};

    template <class Type1> struct all_of <front, vector <Type1>> : Type1 {};

    template <class Type1, class ... Types>
        struct all_of <front, vector <Type1, Types ...>>
    : implementation::all_of_vector <Type1::value, Types ...> {};

} // namespace meta

#endif // META_ALL_OF_HPP_INCLUDED
