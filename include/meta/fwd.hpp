// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

/** \file
Forward definitions for the meta namespace.
*/
#ifndef META_FWD_HPP_INCLUDED
#define META_FWD_HPP_INCLUDED

// Include a simple header to declare boost::mpl.
#include "boost/mpl/void_fwd.hpp"

namespace meta {

namespace mpl = boost::mpl;

// Hooks for specialisation.
template <typename Range> struct range_tag;

namespace operation {

    // For back-off: only one should be enabled for one Range!
    template <typename Range, typename Enable = void> struct range_tag_back_off;

    template <typename Tag> struct default_direction;
    template <typename Tag, typename Direction> struct empty;
    template <typename Tag, typename Direction> struct size;
    template <typename Tag, typename Direction> struct first;

    // Define either of these.
    template <typename Tag, typename Direction> struct drop_one;
    template <typename Tag, typename Direction, typename Number> struct drop;

    template <typename Tag, typename Direction> struct push;
    template <typename Tag, typename Direction> struct insert;

    // Does not have to be specialised: the default implementation works.
    template <typename Tag, typename Direction> struct contains;

    // Key-based containers: no direction.
    template <typename Tag> struct has_key;
    template <typename Tag> struct at;
    template <typename Tag> struct remove;

    // Does not have to be specialised: the default implementation works.
    template <typename Tag, typename Direction> struct fold;
    template <typename Tag, typename Direction> struct fold_reverse;
    template <typename Tag, typename Direction> struct fold_reverse_1;

    // Less intrinsic but optimisable.
    template <typename RangeTag, typename Direction> struct find;
    template <typename Tag1, typename Tag2, typename Direction>
    struct concatenate;

}  // namespace operation

// Declaring these makes it possible for algorithms to optimise for them.
template <typename Function, typename Range> struct transform;

template <typename... Types> struct vector;

}  // namespace meta

#endif  // META_FWD_HPP_INCLUDED
