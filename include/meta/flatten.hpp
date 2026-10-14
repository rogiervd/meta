// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_FLATTEN_HPP_INCLUDED
#define META_FLATTEN_HPP_INCLUDED

#include "meta/concatenate.hpp"
#include "meta/fold.hpp"
#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/vector.hpp"

#include <boost/mpl/placeholders.hpp>

namespace meta {

template <typename Direction, typename Sequences = void> struct flatten;

template <typename Sequences> struct flatten<Sequences>
: flatten<typename default_direction<Sequences>::type, Sequences> {};

namespace flatten_detail {

    // Implementation: depends on whether Sequences is empty.
    template <
        typename Direction, typename Sequences,
        bool Empty = meta::empty<Direction, Sequences>::value>
    struct flatten;

    template <typename Direction, typename Sequences>
    struct flatten<Direction, Sequences, true>
    {
        typedef Sequences type;
    };

    template <typename Direction, typename Sequences>
    struct flatten<Direction, Sequences, false>
    : fold<Direction, meta::concatenate<mpl::_, mpl::_>, Sequences> {};

}  // namespace flatten_detail

template <typename Direction, typename Sequences> struct flatten
: flatten_detail::flatten<Direction, Sequences> {};

}  // namespace meta

#endif  // META_FLATTEN_HPP_INCLUDED
