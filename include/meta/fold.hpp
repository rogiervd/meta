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

#ifndef META_FOLD_HPP_INCLUDED
#define META_FOLD_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/mpl/eval_if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Apply Function to each element of the Sequence and use its result type
    as a parameter for the next.
    If the Sequence contains T1, T2, and T3, then the result of Fold is
    apply <Function, apply <Function, apply <Function, State, T1>, T2>, T3>
    If State is left out, then the first element is used as the State.
    */
    template <typename Direction, typename Function, typename State = void,
            typename Range = void>
        struct fold
    : operation::fold <typename range_tag <Range>::type, Direction>::template
        apply <Function, State, Range> {};

    // Without Direction
    template <typename Function, typename Range>
        struct fold <Function, Range, void,
            typename boost::disable_if <is_direction <Function> >::type>
    : fold <typename default_direction <Range>::type, Function, Range> {};

    template <typename Function, typename State, typename Range>
        struct fold <Function, State, Range,
            typename boost::disable_if <is_direction <Function> >::type>
    : fold <typename default_direction <Range>::type, Function, State, Range>
    {};

    // Without State: use the first element as state.
    template <typename Direction, typename Function, typename Range>
        struct fold <Direction, Function, Range,
            typename boost::enable_if <is_direction <Direction> >::type>
    : fold <Direction, Function,
        typename first <Direction, Range>::type,
        typename drop <Direction, Range>::type
    > {};

    namespace operation {
        /**
        Default implementation: uses first and drop.
        */
        template <typename Tag, typename Direction> struct fold
        {
            template <typename Function, typename State, typename Range,
                bool empty = meta::empty <Direction, Range>::value>
            struct apply;

            template <typename Function, typename State,
                typename Range>
            struct apply <Function, State, Range, true>
            { typedef State type; };

            template <typename Function, typename State,
                typename Range>
            struct apply <Function, State, Range, false>
            : apply <Function,
                typename mpl::apply <Function, State,
                    typename meta::first <Direction, Range>::type>::type,
                typename meta::drop <Direction, Range>::type
            > {};
        };
    } // namespace operation

} // namespace meta

#endif  // META_FOLD_HPP_INCLUDED

