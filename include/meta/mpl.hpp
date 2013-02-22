/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

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

/**
Converters for MPL sequences.
MPL sequences normally use iterators, which is highly inappropriate for
compile-time, and therefore immutable, sequences.
This file provides a partial wrapper that brings the MPL syntax in line with
range operations.
It uses the same direction::front and direction::back types that ranges use.
*/

#ifndef RANGE_META_MPL_HPP_INCLUDED
#define RANGE_META_MPL_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/is_sequence.hpp>

#include <boost/utility/enable_if.hpp>

namespace meta {

    struct mpl_sequence_tag;

    namespace operation {

        // Allow partial specialisation of meta::range_tag for things that
        // also are MPL sequences.
        template <typename Range>
            struct range_tag_back_off <Range,
                typename boost::enable_if <mpl::is_sequence <Range> >::type>
        {
            typedef mpl_sequence_tag type;
        };

        template <> struct default_direction <mpl_sequence_tag> {
            template <typename Range> struct apply
            { typedef front type; };
        };

        // empty
        template <> struct empty <mpl_sequence_tag, meta::front> {
            template <typename Range> struct apply
            : mpl::empty <Range> {};
        };
        template <> struct empty <mpl_sequence_tag, meta::back>
        : empty <mpl_sequence_tag, meta::front> {};

        // size
        template <> struct size <mpl_sequence_tag, meta::front> {
            template <typename Range> struct apply
            : mpl::size <Range> {};
        };
        template <> struct size <mpl_sequence_tag, meta::back>
        : size <mpl_sequence_tag, meta::front> {};

        // first
        template <> struct first <mpl_sequence_tag, meta::front> {
            template <typename Range> struct apply
            : mpl::front <Range> {};
        };
        template <> struct first <mpl_sequence_tag, meta::back> {
            template <typename Range> struct apply
            : mpl::back <Range> {};
        };

        // drop_one
        template <> struct drop_one <mpl_sequence_tag, meta::front> {
            template <typename Range> struct apply
            : mpl::pop_front <Range> {};
        };
        template <> struct drop_one <mpl_sequence_tag, meta::back> {
            template <typename Range> struct apply
            : mpl::pop_back <Range> {};
        };

        // drop
        template <typename Increment>
            struct drop <mpl_sequence_tag, meta::front, Increment>
        {
            template <typename Range> struct apply
            {
                typedef typename mpl::begin <Range>::type erase_begin;
                typedef typename mpl::advance <erase_begin, Increment>::type
                    erase_end;

                typedef typename mpl::erase <
                        Range, erase_begin, erase_end
                    >::type type;
            };
        };
        template <typename Increment>
            struct drop <mpl_sequence_tag, meta::back, Increment>
        {
            template <typename Range> struct apply
            {
                typedef typename mpl::end <Range>::type erase_end;
                typedef typename mpl::advance <erase_end,
                    typename mpl::negate <Increment>::type>::type erase_begin;

                typedef typename mpl::erase <
                        Range, erase_begin, erase_end
                    >::type type;
            };
        };

        // push
        template <> struct push <mpl_sequence_tag, meta::front> {
            template <typename NewElement, typename Range> struct apply
            : mpl::push_front <Range, NewElement> {};
        };
        template <> struct push <mpl_sequence_tag, meta::back>
        {
            template <typename NewElement, typename Range> struct apply
            : mpl::push_back <Range, NewElement> {};
        };

        // fold
        template <> struct fold <mpl_sequence_tag, meta::front> {
            template <typename Function, typename State, typename Range>
                struct apply
            : mpl::fold <Range, State, Function> {};
        };
        template <> struct fold <mpl_sequence_tag, meta::back> {
            template <typename Function, typename State, typename Range>
                struct apply
            : mpl::reverse_fold <Range, State, Function> {};
        };

    } // namespace operation

} // namespace meta

#endif  // RANGE_META_MPL_HPP_INCLUDED

