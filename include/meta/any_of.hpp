/*
Copyright 2013, 2015 Rogier van Dalen.

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

#ifndef META_ANY_OF_HPP_INCLUDED
#define META_ANY_OF_HPP_INCLUDED

#include <boost/mpl/if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Return true iff any element in Range is true.
    If Range is empty, then return false.
    Direction can be left out.
    */
    template <typename Direction, typename Range = void> struct any_of;

    template <typename Range> struct any_of <Range>
    : any_of <typename default_direction <Range>::type, Range> {};

    namespace implementation {
        template <typename Direction, typename Range> struct any_of_non_empty
        : mpl::if_ <typename first <Direction, Range>::type,
            mpl::true_,
            meta::any_of <Direction, typename drop <Direction, Range>::type>
            >::type {};
    } // namespace implementation

    template <typename Direction, typename Range> struct any_of
    : mpl::if_ <empty <Direction, Range>,
        mpl::false_, implementation::any_of_non_empty <Direction, Range>>::type
    {};

    /*
    Specialisation for vector.
    In profiling template instantiations in a real project, this turned out a
    bottleneck.
    If the first type is false, then the rest should not be evaluated.
    It is therefore not possible to get this below O(n) instantiations.
    */
    namespace implementation {

        template <bool first, class ... Types> struct any_of_vector;

        template <class ... Types> struct any_of_vector <true, Types ...>
        : boost::mpl::true_ {};

        template <> struct any_of_vector <false>
        : boost::mpl::false_ {};

        template <class Next, class ... Types>
            struct any_of_vector <false, Next, Types ...>
        : any_of_vector <Next::value, Types...> {};

    } // namespace implementation

    // Without direction.

    template <> struct any_of <vector<>> : mpl::false_ {};

    template <class Type1> struct any_of <vector <Type1>> : Type1 {};

    template <class Type1, class ... Types>
        struct any_of <vector <Type1, Types ...>>
    : implementation::any_of_vector <Type1::value, Types ...> {};

    // With direction.

    template <> struct any_of <front, vector<>> : mpl::false_ {};

    template <class Type1> struct any_of <front, vector <Type1>> : Type1 {};

    template <class Type1, class ... Types>
        struct any_of <front, vector <Type1, Types ...>>
    : implementation::any_of_vector <Type1::value, Types ...> {};

} // namespace meta

#endif // META_ANY_OF_HPP_INCLUDED
