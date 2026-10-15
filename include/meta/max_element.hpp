// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_MAX_ELEMENT_HPP
#define META_MAX_ELEMENT_HPP

#include "meta/fold.hpp"
#include "meta/fwd.hpp"  // IWYU pragma: keep
#include "meta/range.hpp"

namespace meta {

template <typename Direction, typename Range = void> struct max_element;

template <typename Range> struct max_element<Range>
: max_element<typename default_direction<Range>::type, Range> {};

namespace max_element_detail {
    struct max_of_two
    {
        // If we were to use mpl::max here, it would refuse to work with
        // std::integral_constant, because it lacks tags that Boost.MPL
        // expects.
        template <
            typename First, typename Second,
            bool less = (First::value < Second::value)>
        struct apply;

        template <typename First, typename Second>
        struct apply<First, Second, true> : Second {};
        template <typename First, typename Second>
        struct apply<First, Second, false> : First {};
    };
}  // namespace max_element_detail

template <typename Direction, typename Range> struct max_element
: fold<Direction, max_element_detail::max_of_two, Range> {};

}  // namespace meta

#endif  // META_MAX_ELEMENT_HPP
