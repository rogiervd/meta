/*
Copyright 2013 Rogier van Dalen.

This file is part of Rogier van Dalen's meta-programming library for C++.

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

#ifndef META_TAKE_HPP_INCLUDED
#define META_TAKE_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/min.hpp>
#include <boost/mpl/or.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    template <class Direction, class RangeTag> struct take_tag;

    template <class Direction, class Limit, class Underlying /*= void*/>
        struct take
    {
        typedef take type;

    private:
        typedef Direction direction;
        typedef Limit limit;
        typedef Underlying underlying;
        typedef typename range_tag <Underlying>::type underlying_tag;

        // Operations need access to all typedefs because of default arguments.
        template <class Take> friend struct range_tag;
        friend struct operation::default_direction <
            take_tag <Direction, underlying_tag>>;
        friend struct operation::empty <
            take_tag <Direction, underlying_tag>, Direction>;
        friend struct operation::size <
            take_tag <Direction, underlying_tag>, Direction>;
        friend struct operation::first <
            take_tag <Direction, underlying_tag>, Direction>;
        template <class RangeTag, class Direction2, class Increment>
            friend struct operation::drop;
    };

    // Without Direction
    template <class Limit, class Underlying>
        struct take <Limit, Underlying,
            typename boost::disable_if <is_direction <Limit>>::type>
    : take <typename default_direction <Underlying>::type, Limit, Underlying>
    {};

    template <class Direction, class Limit, class Underlying>
        struct range_tag <take <Direction, Limit, Underlying>>
    {
        typedef take <Direction, Limit, Underlying> take_type;
        typedef take_tag <typename take_type::direction,
            typename take_type::underlying_tag> type;
    };

    namespace operation {

        template <class Direction, class UnderlyingTag>
            struct default_direction <take_tag <Direction, UnderlyingTag>>
        { template <class Range> struct apply { typedef Direction type; }; };

        // empty.
        template <class Direction, class UnderlyingTag>
            struct empty <take_tag <Direction, UnderlyingTag>, Direction>
        {
            template <class Range> struct apply
            : mpl::or_ <mpl::equal_to <typename Range::limit, mpl::size_t <0>>,
                meta::empty <Direction, typename Range::underlying>> {};
        };

        // size.
        template <class Direction, class UnderlyingTag>
            struct size <take_tag <Direction, UnderlyingTag>, Direction>
        {
            template <class Range> struct apply
            : mpl::min <typename Range::limit,
                meta::size <Direction, typename Range::underlying>>::type {};
        };

        // first.
        template <class Direction, class UnderlyingTag>
            struct first <take_tag <Direction, UnderlyingTag>, Direction>
        {
            template <class Range> struct apply
            : meta::first <Direction, typename Range::underlying> {};
        };

        // drop.
        template <class Direction, class UnderlyingTag, class Increment>
            struct drop <take_tag <Direction, UnderlyingTag>,
                Direction, Increment>
        {
            template <class Range> struct apply {
                typedef take <Direction,
                    mpl::size_t <(Range::limit::value - Increment::value)>,
                    typename meta::drop <Direction, Increment,
                        typename Range::underlying>::type> type;
            };
        };

    } // namespace operation

} // namespace meta

#endif  // META_TAKE_HPP_INCLUDED

