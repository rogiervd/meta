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

#ifndef META_RANGE_HPP_INCLUDED
#define META_RANGE_HPP_INCLUDED

#include <type_traits>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>

#include "meta/fwd.hpp"
#include "direction/tag.hpp"

namespace meta {

    template <typename Range> struct range_tag
    : operation::range_tag_back_off <Range> {};

    namespace operation {

        struct undefined {};

        // By default this does not contain a type "type".
        template <typename Range, typename Enable /*= void*/>
            struct range_tag_back_off
        : undefined {};

    } // namespace operation

    template <typename Range> struct is_range
    : mpl::not_ <std::is_base_of <operation::undefined, range_tag <Range> > >
    {};

    // Re-using direction tags of normal ranges makes meta ranges and normal
    // ranges more easily compatible.
    using ::direction::is_direction;
    using ::direction::front;
    using ::direction::back;

    template <typename Range> struct default_direction
    : operation::default_direction <typename range_tag <Range>::type>::
        template apply <Range> {};

    /* Operations */

    /**
    \return true_ iff the Range is empty.
    \todo Automatically forward to reverse direction?
    */
    template <typename DirectionOrRange, typename Range = void>
        struct empty;

    // Forward to default direction.
    template <typename Range>
        struct empty <Range,
            typename boost::disable_if <is_direction <Range> >::type>
    : empty <typename default_direction <Range>::type, Range> {};

    // Forward to operation
    template <typename Direction, typename Range>
        struct empty
    : operation::empty <typename range_tag <Range>::type, Direction>::template
        apply <Range> {};

    /**
    \return The size of the Range.
    */
    template <typename DirectionOrRange, typename Range = void>
        struct size;

    // Forward to default direction.
    template <typename Range>
        struct size <Range,
            typename boost::enable_if <is_range <Range> >::type>
    : size <typename default_direction <Range>::type, Range> {};

    // Forward to operation
    template <typename Direction, typename Range>
        struct size
    : operation::size <typename range_tag <Range>::type, Direction>::template
        apply <Range> {};

    /**
    \return The first element in the Range from direction Direction.
    */
    template <typename DirectionOrRange, typename Range = void>
        struct first;

    // Forward to default direction.
    template <typename Range>
        struct first <Range,
            typename boost::disable_if <is_direction <Range> >::type>
    : first <typename default_direction <Range>::type, Range> {};

    // Forward to operation
    template <typename Direction, typename Range>
        struct first
    : operation::first <typename range_tag <Range>::type, Direction>::template
        apply <Range> {};

    /**
    \return The range Range without the first Number elements from direction
    Direction.
    */
    template <typename DirectionOrNumberOrRange,
        typename NumberOrRange = void,
        typename Range = void> struct drop;

    template <typename Range>
        struct drop <Range,
            typename boost::enable_if <is_range <Range> >::type>
    : drop <typename default_direction <Range>::type, mpl::size_t <1>, Range>
    {};

    template <typename Direction, typename Range>
        struct drop <Direction, Range,
            typename boost::enable_if <
                mpl::and_ <is_direction <Direction>, is_range <Range> >
            >::type>
    : drop <Direction, mpl::size_t <1>, Range> {};

    template <typename Number, typename Range>
        struct drop <Number, Range,
            typename boost::enable_if <
                mpl::and_ <mpl::not_ <is_direction <Number> >, is_range <Range>>
            >::type>
    : drop <typename default_direction <Range>::type, Number, Range> {};

    template <typename Direction, typename Number, typename Range> struct drop
    : operation::drop <typename range_tag <Range>::type, Direction, Number>
        ::template apply <Range> {};

    /**
    Return the range with an extra element added at the end.
    */
    template <typename Direction, typename NewElement, typename Range
            = void>
        struct push;

    template <typename NewElement, typename Range>
        struct push <NewElement, Range>
    : push <typename default_direction <Range>::type, NewElement, Range> {};

    template <typename Direction, typename NewElement, typename Range>
        struct push
    : operation::push <typename range_tag <Range>::type, Direction>
        ::template apply <NewElement, Range> {};

    /**
    Return the range with an extra element inserted in an undefined position.
    */
    template <class Direction, class NewElement, class Range = void>
        struct insert;

    template <class NewElement, class Range> struct insert <NewElement, Range>
    : insert <typename default_direction <Range>::type, NewElement, Range> {};

    template <class Direction, class NewElement, class Range> struct insert
    : operation::insert <typename range_tag <Range>::type, Direction>
        ::template apply <NewElement, Range> {};

    /**
    Return whether a key is in the range.
    */
    template <class Key, class Range> struct has_key
    : operation::has_key <typename range_tag <Range>::type>
        ::template apply <Key, Range> {};

    /**
    Return the element at a key.
    */
    template <class Key, class Range> struct at
    : operation::at <typename range_tag <Range>::type>
        ::template apply <Key, Range> {};

    /**
    Remove the element at a key.
    */
    template <class Key, class Range> struct remove
    : operation::remove <typename range_tag <Range>::type>
        ::template apply <Key, Range> {};

    // Default implementation for drop/drop_one
    namespace operation {

        template <typename Tag, typename Direction, std::size_t number>
            struct drop_general;

        template <typename Tag, typename Direction>
            struct drop_general <Tag, Direction, 0>
        {
            template <typename Range> struct apply
            { typedef Range type; };
        };

        template <typename Tag, typename Direction>
            struct drop_general <Tag, Direction, 1>
        : drop_one <Tag, Direction> {};

        // Apply drop_one repeatedly
        template <typename Tag, typename Direction, std::size_t number>
            struct drop_general
        {
            /*
            drop_one must be applied repeatedly, which involves recursion, which
            involves decomposing "number" up into 1 + rest or rest + 1.
            The former seems to be ever so slightly faster in a real test.
            */
            template <typename Range> struct apply
            : meta::drop <Direction,
                typename drop_general <Tag, Direction, number - 1>::template
                    apply <Range>::type> {};
            /*: drop_general <Tag, Direction, number - 1>::template
                apply <typename meta::drop <Direction, Range>::type> {};*/
        };

        /**
        Default implementation: try to forward to drop_one.
        */
        template <typename Tag, typename Direction, typename Number>
            struct drop
        : drop_general <Tag, Direction, Number::value> {};

        /**
        Default implementation: try to forward to drop.
        */
        template <typename Tag, typename Direction> struct drop_one
        : drop <Tag, Direction, mpl::size_t <1> >
        {};

    } // namespace operation

} // namespace meta

#endif  // META_RANGE_HPP_INCLUDED

