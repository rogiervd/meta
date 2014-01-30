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

#ifndef META_SORT_HPP_INCLUDED
#define META_SORT_HPP_INCLUDED

#include <type_traits>

#include <boost/mpl/or.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/identity.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/single_view.hpp"
#include "meta/merge.hpp"

namespace meta {

    /** \struct sort
    Sort a sequence of types (for example, compile-time constants).
    This is done with a lazy merge-sort.
    Evaluating \c type takes a constant number of template instantiations.
    This sets up a hierarchy of lazy merges.
    Each additional \c drop then causes a number of instantiations logarithmic
    in the length of \c Range.
    To sort the whole range therefore requires O(n log n) instantiations, which
    is exactly what is expected from a sort algorithm.

    \tparam Direction The direction to traverse the range.
        \c default_direction is used if the direction is not given.
    \tparam Compare The predicate for comparison.
        \c mpl::less is used if it is not given.
    \tparam Range The range that is to be sorted.
        It needs to provide \c first and \c drop in the given direction,
        but nothing else is required.
    */
    template <class Direction, class Compare = void, class Range = void>
        struct sort;

    // Only direction: insert mpl::less <...>.
    template <class Direction, class Range>
        struct sort <Direction, Range,
            typename boost::enable_if <is_direction <Direction>>::type>
    : sort <Direction, mpl::less <mpl::_1, mpl::_2>, Range> {};

    // Only Compare: insert default direction.
    template <class Compare, class Range>
        struct sort <Compare, Range,
            typename boost::disable_if <boost::mpl::or_ <
                is_direction <Compare>, std::is_same <Range, void>>>::type>
    : sort <typename default_direction <Range>::type, Compare, Range> {};

    // No parameters: insert default direction.
    template <class Range> struct sort <Range>
    : sort <typename default_direction <Range>::type, Range> {};

    namespace sort_detail {

        /**
        Return a pair with a range containing the first \c 2**depth elements
        from \c Rest in order, and Rest without those first elements.
        If \c Rest has fewer elements then 2**depth, then return a pair with an
        range with all of them in order, and an empty range.
        */
        template <class Direction, class Compare, int Depth, class Rest>
            class sort_part;

        /**
        Return a range with all \c 2**(Depth-1) elements of sorted range
        \c First and the first \c 2**(depth-1) elements of \c Rest, or less if
        \c Rest is exhausted.
        Also return the remainder of \c Rest as second element of the pair.
        */
        template <class Direction, class Compare, int Depth,
                class First, class Rest>
            class sort_part_with;

        /* sort_part. */
        // Depth == 0: Sorted range of length 2**0 = 1: trivial.
        template <class Direction, class Compare, class Rest>
            class sort_part <Direction, Compare, 0, Rest>
        {
            BOOST_MPL_ASSERT_NOT ((meta::empty <Direction, Rest>));
            typedef typename first <Direction, Rest>::type head;
        public:
            typedef mpl::pair <single_view <Direction, head>,
                typename drop <Direction, Rest>::type> type;
        };

        // Depth > 0.
        template <class Direction, class Compare, int Depth, class Rest>
            class sort_part
        {
            BOOST_MPL_ASSERT_NOT ((meta::empty <Direction, Rest>));
            static_assert (Depth > 0, "");

            // Find the first half.
            typedef typename sort_part <Direction, Compare, Depth-1, Rest>::type
                first_part;
            typedef typename first_part::first first;
            typedef typename first_part::second first_rest;
        public:
            typedef typename mpl::eval_if <empty <Direction, first_rest>,
                // We want something of depth Depth, but there are not enough
                // elements to produce it.
                mpl::pair <first, first_rest>,
                // Oherwise, combine the first half with the second half.
                sort_part_with <Direction, Compare, Depth, first, first_rest>
                >::type type;
        };

        /* sort_part_with. */
        template <class Direction, class Compare, int Depth,
                class First, class Rest>
            class sort_part_with
        {
            static_assert (Depth >= 1, "");

            // Sort second part.
            typedef typename sort_part <Direction, Compare, Depth-1, Rest>::type
                second_part;
        public:
            typedef mpl::pair <
                merge <Direction, Compare, First, typename second_part::first>,
                typename second_part::second> type;
        };

        /** \struct sort_at_least_with.
        Try to sort with depth Depth.
        If \c Rest is then not exhausted, try Depth+1, recursively, and so on.
        */
        template <class Direction, class Compare, int Depth,
                class First, class Rest>
            class sort_at_least_with
        {
            static_assert (Depth >= 1, "");
            BOOST_MPL_ASSERT_NOT ((empty <Direction, Rest>));

            typedef typename sort_part_with <
                Direction, Compare, Depth, First, Rest>::type current;
        public:
            typedef typename mpl::eval_if <
                empty <Direction, typename current::second>,
                mpl::first <current>,
                sort_at_least_with <Direction, Compare, Depth+1,
                    typename current::first, typename current::second>
                >::type type;
        };

        template <class Direction, class Compare, class Range>
            struct sort_non_empty
        : mpl::eval_if <
            empty <Direction, typename drop <Direction, Range>::type>,
            // Only one element.
            mpl::identity <Range>,
            // At least two elements.
            sort_at_least_with <Direction, Compare, 1,
                single_view <Direction,
                    typename first <Direction, Range>::type>,
                typename drop <Direction, Range>::type>
        > {};

    } // namespace sort_detail

    /* sort. */
    template <class Direction, class Compare, class Range> struct sort
    : mpl::eval_if <empty <Direction, Range>,
        mpl::identity <Range>,
        sort_detail::sort_non_empty <Direction, Compare, Range>> {};

} // namespace meta

#endif  // META_SORT_HPP_INCLUDED

