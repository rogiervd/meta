/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Meta-programming library for C++.

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
Provide a simple forward list for testing the Meta-programming library.
*/

#ifndef META_TEST_LIST_HPP_INCLUDED
#define META_TEST_LIST_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/fold_reverse.hpp"
#include "direction/tag.hpp"

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/bool.hpp>

namespace meta {
    struct list_direction;
    struct FORGOTTEN_EXPLICIT_DIRECTION_TAG;
} // namespace meta

namespace direction {
    template <> struct is_direction_bare <meta::list_direction>
    : boost::mpl::true_ {};
} // namespace direction

namespace meta {
    /**
    A minimal meta-list, used to test range operations on.
    The point of this list is that it is fully functional but does as little
    as possible itself, so as to be able to test the behaviour of range.hpp.

    The default direction of this list is list_direction, so that if the
    algorithm to be tested by accident uses meta::front, this will produce an
    error.
    */
    template <typename ... Types> struct list;

    template <typename FirstType, typename ... Types>
        struct list <FirstType, Types ...>
    {
        typedef list type;

        typedef FirstType head;
        typedef list <Types ...> tail;

        static const std::size_t size = tail::size + 1;
    };

    template <> struct list <> {
        typedef list type;
        static const std::size_t size = 0;
    };

    template <std::size_t Size> struct list_tag;

    template <typename ... Types> struct range_tag <list <Types ...> >
    { typedef list_tag <list <Types ...>::size> type; };

    // as_list implicitly tests empty, first, and drop.
    template <class Range> struct as_list
    : meta::fold_reverse <meta::list_direction,
        meta::push <meta::list_direction, mpl::_1, mpl::_2>,
        meta::list<>, Range>
    {};

    /**
    A meta-list similar to "list", but with an invalid default direction.
    This means that a direction needs to be passed in to all algorithms, and
    if an algorithm forgets it along the way, it causes a compile error.
    */
    template <typename ... Types> struct weird_list;
    template <typename FirstType, typename ... Types>
        struct weird_list <FirstType, Types ...>
    {
        typedef weird_list type;

        typedef FirstType head;
        typedef weird_list <Types ...> tail;

        static const std::size_t size = tail::size + 1;
    };
    template <> struct weird_list <> {
        typedef weird_list type;
        static const std::size_t size = 0;
    };

    template <typename ... Types> struct range_tag <weird_list <Types ...> >
    { typedef list_tag <weird_list <Types ...>::size> type; };

    namespace operation {

        template <std::size_t Size> struct default_direction <list_tag <Size> >
        {
            template <typename List> struct apply;

            template <typename ... Types>
                struct apply <meta::list <Types ...> >
            { typedef meta::list_direction type; };

            // For testing purposes, the default direction of weird_list is not
            // list_direction!
            // This means that if I have forgotten to propagate a direction tag
            // in some algorithm and I'm relying on default_direction, this
            // causes an error.
            template <typename ... Types>
                struct apply <meta::weird_list <Types ...> >
            {
                typedef meta::FORGOTTEN_EXPLICIT_DIRECTION_TAG type;
            };
        };

        // empty
        template <std::size_t Size>
            struct empty <list_tag <Size>, list_direction>
        { template <typename List> struct apply : mpl::false_ {}; };
        template <> struct empty <list_tag <0>, list_direction>
        { template <typename List> struct apply : mpl::true_ {}; };

        // size
        template <std::size_t Size>
            struct size <list_tag <Size>, list_direction>
        { template <typename List> struct apply : mpl::size_t <Size> {}; };

        // first
        template <std::size_t Size>
            struct first <list_tag <Size>, list_direction>
        {
            template <typename List> struct apply
            { typedef typename List::head type; };
        };
        // Not implementable
        template <> struct first <list_tag <0>, list_direction> {};

        // drop_one
        template <std::size_t Size>
            struct drop_one <list_tag <Size>, list_direction>
        {
            template <typename List> struct apply
            { typedef typename List::tail type; };
        };
        // Not implementable
        template <> struct drop_one <list_tag <0>, list_direction> {};

        // push
        template <std::size_t Size>
            struct push <list_tag <Size>, list_direction>
        {
            template <typename NewElement, typename List> struct apply;

            template <typename NewElement, typename ... Types>
                struct apply <NewElement, list <Types ...> >
            { typedef list <NewElement, Types ...> type; };

            template <typename NewElement, typename ... Types>
                struct apply <NewElement, weird_list <Types ...> >
            { typedef weird_list <NewElement, Types ...> type; };
        };

    } // namespace operation

} // namespace meta

#endif  // META_TEST_LIST_HPP_INCLUDED

