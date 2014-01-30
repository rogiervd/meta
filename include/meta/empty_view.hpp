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

#ifndef META_EMPTY_VIEW_HPP_INCLUDED
#define META_EMPTY_VIEW_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /** \struct empty_view
    Empty range.
    The direction of traversal can be specified; if not, it is "front".

    \tparam Direction The direction of traversal.
        If left out, front is used.
    */
    template <class Direction = front> struct empty_view {};

    template <class Direction> struct empty_view_tag;

    template <class Direction> struct range_tag <empty_view <Direction>>
    { typedef empty_view_tag <Direction> type; };

    namespace operation {

        template <class Direction>
            struct default_direction <empty_view_tag <Direction>>
        { template <class Range> struct apply { typedef Direction type; }; };

        template <class Direction>
            struct empty <empty_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::true_ {}; };

        template <class Direction>
            struct size <empty_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::size_t <0> {}; };

    } // namespace operation

} // namespace meta

#endif  // META_EMPTY_VIEW_HPP_INCLUDED

