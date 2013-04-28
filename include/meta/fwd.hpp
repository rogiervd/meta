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

/** \file
Forward definitions for the meta namespace.
*/
#ifndef META_FWD_HPP_INCLUDED
#define META_FWD_HPP_INCLUDED

namespace meta {

    namespace mpl = boost::mpl;

    // Hooks for specialisation.
    template <typename Range> struct range_tag;

    namespace operation {

        // For back-off: only one should be enabled for one Range!
        template <typename Range, typename Enable = void>
            struct range_tag_back_off;

        template <typename Tag> struct default_direction;
        template <typename Tag, typename Direction> struct empty;
        template <typename Tag, typename Direction> struct size;
        template <typename Tag, typename Direction> struct first;

        // Define either of these.
        template <typename Tag, typename Direction> struct drop_one;
        template <typename Tag, typename Direction, typename Number>
            struct drop;

        template <typename Tag, typename Direction> struct push;

        // Does not have to be specialised: the default implementation works.
        template <typename Tag, typename Direction> struct fold;
        template <typename Tag, typename Direction> struct fold_reverse;
        template <typename Tag, typename Direction> struct fold_reverse_1;

        // Less intrinsic but optimisable.
        template <typename Tag, typename Direction> struct transform;
        template <typename RangeTag, typename Direction> struct find;
        template <typename Tag1, typename Tag2, typename Direction>
            struct concatenate;

    } // namespace operation

    // Never mind the default parameters: they are forwarded to the
    // full-parameter versions in range.hpp.
    template <typename Range> struct default_direction;
    template <typename Direction, typename Range = void> struct empty;
    template <typename Direction, typename Range = void> struct size;
    template <typename Direction, typename Range = void> struct first;
    template <typename Direction, typename Range = void> struct drop_one;
    template <typename Direction, typename Number = void, typename Range = void>
        struct drop;
    template <typename Direction, typename NewElement, typename Range = void>
        struct push;

    template <typename Direction, typename Function, typename State = void,
            typename Sequence = void>
        struct fold;
    template <typename Direction, typename Function, typename State = void,
            typename Sequence = void>
        struct fold_reverse;

    template <typename Direction, typename Function, typename Range = void>
        struct transform;
    template <typename Direction, typename Predicate, typename Range = void>
        struct find;
    template <typename Direction, typename Range1, typename Range2 = void>
        struct concatenate;

    template <typename Direction, typename Sequences = void> struct flatten;

    template <typename Direction, typename Function,
            typename State = void, typename Range = void>
        struct scan;
    template <typename Direction, typename Predicate, typename Range = void>
        struct filter;

    template <typename Direction, typename Predicate,
            typename Range1 = void, typename Range2 = void>
        struct equal;
    template <typename Direction, typename Type, typename Range = void>
        struct contains;

    template <typename Direction, typename Sequence = void> struct enumerate;

    template <typename ... Types> struct vector;

} // namespace meta

#endif  // META_FWD_HPP_INCLUDED

