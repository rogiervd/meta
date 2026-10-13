// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_FIND_HPP_INCLUDED
#define META_FIND_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include "meta/range.hpp"

namespace meta {

template <typename Direction, typename Predicate, typename Range = void>
struct find;

template <typename Predicate, typename Range> struct find<Predicate, Range>
: find<typename default_direction<Range>::type, Predicate, Range> {};

namespace operation {

    // Default implementation
    template <typename RangeTag, typename Direction> struct find
    {
        template <
            typename Predicate, typename Range,
            bool empty = meta::empty<Direction, Range>::value>
        struct apply;

        template <typename Predicate, typename Range>
        struct apply<Predicate, Range, true>
        {
            typedef Range type;
        };

        template <typename Predicate, typename Range>
        struct apply<Predicate, Range, false>
        : mpl::eval_if<
              typename mpl::apply<
                  Predicate,
                  typename meta::first<Direction, Range>::type>::type,
              mpl::identity<Range>,
              meta::find<
                  Direction, Predicate,
                  typename meta::drop<Direction, Range>::type>> {};
    };

}  // namespace operation

template <typename Direction, typename Predicate, typename Range> struct find
: operation::find<typename range_tag<Range>::type, Direction>::template apply<
      Predicate, Range>::type {};

}  // namespace meta

#endif  // META_FIND_HPP_INCLUDED
