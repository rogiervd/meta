/*
Copyright 2011, 2012, 2014 Rogier van Dalen.

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

#ifndef META_FILTER_HPP_INCLUDED
#define META_FILTER_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace meta {

    template <typename Predicate, typename Range> struct filter
    { typedef filter type; };

    struct filter_tag;

    template <typename Predicate, typename Range>
        struct range_tag <filter <Predicate, Range>>
    { typedef filter_tag type; };

    template <typename Predicate, typename Range>
        struct default_direction <filter <Predicate, Range>>
    : default_direction <Range> {};

    namespace operation {

        namespace detail {

            /** \internal
            Compute properties of the filtered range.
            */
            template <typename Direction, typename Predicate, typename Range,
                    bool Empty = meta::empty <Direction, Range>::value>
                struct filter_traits;

            // Empty.
            template <typename Direction, typename Predicate, typename Range>
                struct filter_traits <Direction, Predicate, Range, true>
            { typedef mpl::true_ empty; };

            // Non-empty: return first element f
            template <typename Direction, typename Predicate, typename Range>
                struct filter_traits_when_non_empty
            {
                typedef mpl::false_ empty;
                typedef meta::first <Direction, Range> first;
                typedef meta::filter <Predicate,
                    typename meta::drop <Direction, Range>::type> next_filter;
            };

            template <typename Direction, typename Predicate, typename Range>
                struct filter_traits <Direction, Predicate, Range, false>
            : mpl::if_ <
                // If predicate is true for the first element,
                typename mpl::apply <Predicate, typename
                    meta::first <Direction, Range>::type>::type,
                // forward to filter_traits_when_non_empty;
                filter_traits_when_non_empty <Direction, Predicate, Range>,
                // otherwise, recursively forward to filter_traits.
                filter_traits <Direction, Predicate, typename
                    meta::drop <Direction, Range>::type>
            >::type {};

        } // namespace detail

        template <class Direction> struct empty <filter_tag, Direction> {
            template <class Filter> struct apply;

            template <class Predicate, class Range>
                struct apply <meta::filter <Predicate, Range>>
            : detail::filter_traits <Direction, Predicate, Range>::empty {};
        };

        template <class Direction> struct first <filter_tag, Direction> {
            template <class Filter> struct apply;

            template <class Predicate, class Range>
                struct apply <meta::filter <Predicate, Range>>
            : detail::filter_traits <Direction, Predicate, Range>::first
            {};
        };

        template <class Direction> struct drop_one <filter_tag, Direction> {
            template <class Filter> struct apply;

            template <class Predicate, class Range>
                struct apply <meta::filter <Predicate, Range>>
            {
                typedef typename detail::filter_traits <
                    Direction, Predicate, Range>::next_filter type;
            };
        };

    } // namespace operation

} // namespace meta

#endif  // META_FILTER_HPP_INCLUDED

