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

#ifndef META_TRANSFORM_HPP_INCLUDED
#define META_TRANSFORM_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>

namespace meta {

    template <typename Direction, typename Function, typename Range = void>
        struct transform;

    template <typename Function, typename Range>
        struct transform <Function, Range>
    : transform <typename default_direction <Range>::type, Function, Range> {};

    namespace operation {
        // Generic implementation
        template <typename Tag, typename Direction> struct transform
        {
            template <typename Function, typename Range,
                    bool empty = meta::empty <Direction, Range>::value>
                struct apply;

            template <typename Function, typename Range>
                struct apply <Function, Range, true>
            {
                typedef Range type;
            };

            template <typename Function, typename Range>
                struct apply <Function, Range, false>
            : meta::push <Direction,
                // First: apply Function to first <Range>
                typename mpl::apply <Function,
                    typename meta::first <Direction, Range>::type>::type,
                // Rest: apply recursively.
                typename meta::transform <Direction, Function,
                    typename meta::drop <Direction, Range>::type>::type
            > {};
        };
    } // namespace detail

    template <typename Direction, typename Function, typename Range>
        struct transform
    : operation::transform <typename range_tag <Range>::type, Direction>
        ::template apply <Function, Range> {};

} // namespace meta

#endif  // META_TRANSFORM_HPP_INCLUDED

