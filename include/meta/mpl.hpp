/*
Copyright 2011, 2012 Rogier van Dalen.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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

