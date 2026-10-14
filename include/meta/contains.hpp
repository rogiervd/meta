// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_CONTAINS_HPP_INCLUDED
#define META_CONTAINS_HPP_INCLUDED

#include <type_traits>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>

#include "meta/find.hpp"
#include "meta/range.hpp"

namespace meta {

/**
Shorthand for not_ <empty <find <is_same <Type, _>, Range> > >.

This causes O(n) instantiations with n the length of the range or the first
position of Type.
This may be optimised for a specific container type.
*/
template <class Direction, class Type, class Range = void> struct contains;

template <class Type, class Range> struct contains<Type, Range>
: contains<typename default_direction<Range>::type, Type, Range> {};

template <class Direction, class Type, class Range> struct contains
: operation::contains<
      typename range_tag<Range>::type, Direction>::template apply<Type, Range> {
};

namespace operation {

    template <class Tag, class Direction> struct contains
    {
        template <class Type, class Range> struct apply
        : mpl::not_<meta::empty<
              Direction,
              typename meta::find<
                  Direction, std::is_same<Type, mpl::_>, Range>::type>> {};
    };

}  // namespace operation

}  // namespace meta

#endif  // META_CONTAINS_HPP_INCLUDED
