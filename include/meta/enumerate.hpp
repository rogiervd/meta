// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_ENUMERATE_HPP_INCLUDED
#define META_ENUMERATE_HPP_INCLUDED

#include <cstddef>

#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size_t.hpp>  // IWYU pragma: keep

#include "meta/fwd.hpp"  // IWYU pragma: keep
#include "meta/range.hpp"
#include "meta/scan.hpp"

namespace meta {

template <typename Direction, typename Range = void> struct enumerate;

template <typename Range> struct enumerate<Range>
: enumerate<typename default_direction<Range>::type, Range> {};

template <typename Direction, typename Range> struct enumerate
{
    // Initialise with the before-the-begin element (-1, void).
    typedef mpl::pair<mpl::size_t<std::size_t(-1)>, void> before_begin;

    // Implementation without lambdas is faster.
    struct function
    {
        template <typename Previous, typename Type> struct apply
        {
            typedef typename mpl::next<typename Previous::first>::type number;
            typedef mpl::pair<number, Type> type;
        };
    };

    // Enumerated list of types that starts with (-1, void).
    typedef scan<Direction, function, before_begin, Range> elements;
    // Remove the (-1, void)
    typedef typename drop<Direction, elements>::type type;
};

}  // namespace meta

#endif  // META_ENUMERATE_HPP_INCLUDED
