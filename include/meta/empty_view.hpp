// SPDX-FileCopyrightText: Copyright 2013 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

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

template <class Direction> struct range_tag<empty_view<Direction>>
{
    typedef empty_view_tag<Direction> type;
};

namespace operation {

    template <class Direction>
    struct default_direction<empty_view_tag<Direction>>
    {
        template <class Range> struct apply
        {
            typedef Direction type;
        };
    };

    template <class Direction>
    struct empty<empty_view_tag<Direction>, Direction>
    {
        template <class Range> struct apply : mpl::true_ {};
    };

    template <class Direction> struct size<empty_view_tag<Direction>, Direction>
    {
        template <class Range> struct apply : mpl::size_t<0> {};
    };

}  // namespace operation

}  // namespace meta

#endif  // META_EMPTY_VIEW_HPP_INCLUDED
