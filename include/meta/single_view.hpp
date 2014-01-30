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

#ifndef META_SINGLE_VIEW_HPP_INCLUDED
#define META_SINGLE_VIEW_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/empty_view.hpp"

namespace meta {

    /** \struct single_view
    Range with only one element.
    This is useful as a basic class in defining some more complicated ranges.
    The direction of traversal can be specified; if not, it is "front".

    \tparam Direction The direction of traversal.
        If left out, front is used.
    \tparam Element The first and only element.
    */
    template <class ... Arguments> struct single_view;

    template <class Direction, class Element>
        struct single_view <Direction, Element>
    {
        typedef single_view type;
        typedef Direction direction;
        typedef Element element;
    };

    template <class Element> struct single_view <Element>
    : single_view <front, Element> {};

    template <class Direction> struct single_view_tag;

    template <class ... Arguments>
        struct range_tag <single_view <Arguments ...>>
    {
        typedef single_view_tag <
            typename single_view <Arguments ...>::direction> type;
    };

    namespace operation {

        template <class Direction>
            struct default_direction <single_view_tag <Direction>>
        { template <class Range> struct apply { typedef Direction type; }; };

        template <class Direction>
            struct empty <single_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::false_ {}; };

        template <class Direction>
            struct size <single_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::size_t <1> {}; };

        template <class Direction>
            struct first <single_view_tag <Direction>, Direction>
        {
            template <class Range> struct apply
            { typedef typename Range::element type; };
        };

        template <class Direction>
            struct drop_one <single_view_tag <Direction>, Direction>
        {
            template <class Range> struct apply
            { typedef empty_view <Direction> type; };
        };

    } // namespace operation

} // namespace meta

#endif  // META_SINGLE_VIEW_HPP_INCLUDED

