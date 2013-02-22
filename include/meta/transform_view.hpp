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

#ifndef META_TRANSFORM_VIEW_HPP_INCLUDED
#define META_TRANSFORM_VIEW_HPP_INCLUDED

#include <boost/mpl/apply.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    struct transform_view_tag;

    template <typename Function, typename Range>
        struct transform_view
    {
        typedef transform_view type;
        typedef Function function;
        typedef Range range;
    };
    template <typename Function, typename Range>
        struct range_tag <transform_view <Function, Range> >
    { typedef transform_view_tag type; };

    template <typename Function, typename Range>
        struct default_direction <transform_view <Function, Range> >
    : default_direction <Range> {};

    namespace operation {

        template <typename Direction>
            struct empty <transform_view_tag, Direction>
        {
            template <typename Range> struct apply;
            template <typename Function, typename Range>
                struct apply <transform_view <Function, Range> >
            : meta::empty <Direction, Range> {};
        };

        template <typename Direction>
            struct size <transform_view_tag, Direction>
        {
            template <typename Range> struct apply;
            template <typename Function, typename Range>
                struct apply <transform_view <Function, Range> >
            : meta::size <Direction, Range> {};
        };

        template <typename Direction>
            struct first <transform_view_tag, Direction>
        {
            template <typename Range> struct apply;
            template <typename Function, typename Range>
                struct apply <transform_view <Function, Range> >
            : mpl::apply <Function,
                typename meta::first <Direction, Range>::type
            > {};
        };

        template <typename Direction, typename Number>
            struct drop <transform_view_tag, Direction, Number>
        {
            template <typename Range> struct apply;
            template <typename Function, typename Range>
                struct apply <transform_view <Function, Range> >
            {
                typedef transform_view <Function,
                    typename meta::drop <Direction, Number, Range>::type> type;
            };
        };

        /// \todo Really do this?
        template <typename Direction>
            struct push <transform_view_tag, Direction>
        {
            template <typename NewElement, typename Range,
                    bool Empty = meta::empty <Direction, Range>::value>
                struct apply;
            template <typename NewElement, typename Function, typename Range>
                struct apply <
                    NewElement, transform_view <Function, Range>, true>
            : meta::push <NewElement, Range> {};
        };

    } // namespace operation

} // namespace meta

#endif  // META_TRANSFORM_VIEW_HPP_INCLUDED

