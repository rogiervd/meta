// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_CONCATENATE_HPP_INCLUDED
#define META_CONCATENATE_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include "boost/mpl/not.hpp"

namespace meta {

/**
Concatenate two ranges.
This means that Range1 is inserted to the front of Range2.
*/
template <typename Direction, typename Range1, typename Range2 = void>
struct concatenate
: operation::concatenate<
      typename range_tag<Range1>::type, typename range_tag<Range2>::type,
      Direction>::template apply<Range1, Range2> {};

template <typename Range1, typename Range2> struct concatenate<Range1, Range2>
: concatenate<typename default_direction<Range2>::type, Range1, Range2> {};

namespace operation {
    /**
    Generic implementation: pushes Range1 to Range2 element-by-element.
    */
    template <typename Tag1, typename Tag2, typename Direction>
    struct concatenate
    {
        template <
            typename Range1, typename Range2,
            bool Empty = meta::empty<Direction, Range1>::value>
        struct apply;

        template <typename Range1, typename Range2>
        struct apply<Range1, Range2, true>
        {
            typedef Range2 type;
        };

        template <typename Range1, typename Range2>
        struct apply<Range1, Range2, false>
        : meta::push<
              Direction, typename meta::first<Direction, Range1>::type,
              typename meta::concatenate<
                  Direction, typename meta::drop<Direction, Range1>::type,
                  Range2>::type> {};
    };
}  // namespace operation

}  // namespace meta

#endif  // META_CONCATENATE_HPP_INCLUDED
