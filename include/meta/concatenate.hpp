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

#ifndef META_CONCATENATE_HPP_INCLUDED
#define META_CONCATENATE_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Concatenate two ranges.
    This means that Range1 is inserted to the front of Range2.
    */
    template <typename Direction, typename Range1, typename Range2 /*= void*/>
        struct concatenate
    : operation::concatenate <
        typename range_tag <Range1>::type, typename range_tag <Range2>::type,
        Direction>::template apply <Range1, Range2> {};

    template <typename Range1, typename Range2>
        struct concatenate <Range1, Range2>
    : concatenate <typename default_direction <Range2>::type, Range1, Range2>
    {};

    namespace operation
    {
        /**
        Generic implementation: pushes Range1 to Range2 element-by-element.
        */
        template <typename Tag1, typename Tag2, typename Direction>
            struct concatenate
        {
            template <typename Range1, typename Range2,
                    bool Empty = meta::empty <Direction, Range1>::value>
                struct apply;

            template <typename Range1, typename Range2>
                struct apply <Range1, Range2, true>
            { typedef Range2 type; };

            template <typename Range1, typename Range2>
                struct apply <Range1, Range2, false>
            : meta::push <Direction,
                typename meta::first <Direction, Range1>::type,
                typename meta::concatenate <Direction,
                    typename meta::drop <Direction, Range1>::type, Range2>::type
            > {};
        };
    }

} // namespace meta

#endif  // META_CONCATENATE_HPP_INCLUDED

