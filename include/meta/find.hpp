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

#ifndef META_FIND_HPP_INCLUDED
#define META_FIND_HPP_INCLUDED

#include "meta/range.hpp"

namespace meta {

    template <typename Direction, typename Predicate, typename Range /*= void*/>
        struct find;

    template <typename Predicate, typename Range>
        struct find <Predicate, Range>
    : find <typename default_direction <Range>::type, Predicate, Range> {};

    namespace operation {

        // Default implementation
        template <typename RangeTag, typename Direction> struct find
        {
            template <typename Predicate, typename Range,
                bool empty = meta::empty <Direction, Range>::value>
            struct apply;

            template <typename Predicate, typename Range>
                struct apply <Predicate, Range, true>
            {
                typedef Range type;
            };

            template <typename Predicate, typename Range>
                struct apply <Predicate, Range, false>
            : mpl::eval_if <
                typename mpl::apply <Predicate,
                    typename meta::first <Direction, Range>::type>::type,
                mpl::identity <Range>,
                meta::find <Direction, Predicate,
                    typename meta::drop <Direction, Range>::type>
            > {};
        };

    } // namespace operation

    template <typename Direction, typename Predicate, typename Range>
        struct find
    : operation::find <typename range_tag <Range>::type, Direction>::
        template apply <Predicate, Range>::type {};

} // namespace meta

#endif  // META_FIND_HPP_INCLUDED

