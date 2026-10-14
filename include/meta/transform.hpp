// SPDX-FileCopyrightText: Copyright 2011, 2012, 2014 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_TRANSFORM_HPP_INCLUDED
#define META_TRANSFORM_HPP_INCLUDED

#include <boost/mpl/apply.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

struct transform_tag;

template <typename Function, typename Range> struct transform
{
    typedef transform type;
    typedef Function function;
    typedef Range range;
};

template <typename Function, typename Range>
struct range_tag<transform<Function, Range>>
{
    typedef transform_tag type;
};

template <typename Function, typename Range>
struct default_direction<transform<Function, Range>>
: default_direction<Range> {};

namespace operation {

    template <typename Direction> struct empty<transform_tag, Direction>
    {
        template <typename Range> struct apply;
        template <typename Function, typename Range>
        struct apply<transform<Function, Range>>
        : meta::empty<Direction, Range> {};
    };

    template <typename Direction> struct size<transform_tag, Direction>
    {
        template <typename Range> struct apply;
        template <typename Function, typename Range>
        struct apply<transform<Function, Range>>
        : meta::size<Direction, Range> {};
    };

    template <typename Direction> struct first<transform_tag, Direction>
    {
        template <typename Range> struct apply;
        template <typename Function, typename Range>
        struct apply<transform<Function, Range>>
        : mpl::apply<Function, typename meta::first<Direction, Range>::type> {};
    };

    template <typename Direction, typename Number>
    struct drop<transform_tag, Direction, Number>
    {
        template <typename Range> struct apply;
        template <typename Function, typename Range>
        struct apply<transform<Function, Range>>
        {
            typedef transform<
                Function, typename meta::drop<Direction, Number, Range>::type>
                type;
        };
    };

}  // namespace operation

}  // namespace meta

#endif  // META_TRANSFORM_HPP_INCLUDED
