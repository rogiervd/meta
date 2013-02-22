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

#ifndef META_FOLD_REVERSE_HPP_INCLUDED
#define META_FOLD_REVERSE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/mpl/eval_if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Apply Function to each element of the Sequence in reverse order and use its
    result type as a parameter for the previous.
    If the Sequence contains T1, T2, and T3, then the result of fold_reverse is
    apply <Function, T1, apply <Function, T2, apply <Function, T3, State> > >
    If State is left out, then the last element is used as the State.

    For fold, when State is not given, first <Range> is used.
    For fold_reverse, however, the very last element of Range is used.
    Therefore, two separate classes are used in namespace operation.
    fold_reverse expects a state; fold_reverse_1 uses the last element of the
    range as the initial state.
    */
    template <typename Direction, typename Function, typename State,
            typename Range>
        struct fold_reverse
    : operation::fold_reverse <typename range_tag <Range>::type, Direction>::
        template apply <Function, State, Range> {};

    // Without Direction: forward to implementation with default_direction.
    template <typename Function, typename Range>
        struct fold_reverse <Function, Range, void,
            typename boost::disable_if <is_direction <Function>>::type>
    : fold_reverse <typename default_direction <Range>::type,
        Function, Range> {};

    template <typename Function, typename State, typename Range>
        struct fold_reverse <Function, State, Range,
            typename boost::disable_if <is_direction <Function> >::type>
    : fold_reverse <typename default_direction <Range>::type,
        Function, State, Range> {};

    // Without State: use the last element as state.
    // Forward to operation::fold_reverse_1.
    template <typename Direction, typename Function, typename Range>
        struct fold_reverse <Direction, Function, Range,
            typename boost::enable_if <is_direction <Direction> >::type>
    : operation::fold_reverse_1 <typename range_tag <Range>::type, Direction>::
        template apply <Function, Range> {};

    namespace operation {

        /**
        Default implementation: uses first and drop.
        With initial state.
        */
        template <typename Tag, typename Direction> struct fold_reverse {
            template <typename Function, typename State, typename Range,
                    bool Empty = meta::empty <Direction, Range>::value>
                struct apply;

            template <typename Function, typename State, typename Range>
            struct apply <Function, State, Range, true>
            { typedef State type; };

            template <typename Function, typename State, typename Range>
            struct apply <Function, State, Range, false>
            : mpl::apply <Function,
                typename meta::first <Direction, Range>::type,
                typename apply <Function, State,
                    typename meta::drop <Direction, Range>::type>::type
            > {};
        };

        /**
        Default implementation: uses first and drop.
        Without initial state.
        */
        template <typename Tag, typename Direction> struct fold_reverse_1
        {
            template <typename Function, typename Range,
                bool TailEmpty = meta::empty <Direction,
                    typename meta::drop <Direction, Range>::type>::value>
                struct apply;

            template <typename Function, typename Range>
                struct apply <Function, Range, true>
            : meta::first <Direction, Range> {};

            template <typename Function, typename Range>
                struct apply <Function, Range, false>
            : mpl::apply <Function,
                typename meta::first <Direction, Range>::type,
                typename apply <Function,
                    typename meta::drop <Direction, Range>::type>::type
            > {};
        };

    } // namespace operation

} // namespace meta

#endif  // META_FOLD_REVERSE_HPP_INCLUDED

