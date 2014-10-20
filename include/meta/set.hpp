/*
Copyright 2011, 2012, 2014 Rogier van Dalen.

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

/** \file
Define meta::set, an MPL sequence that can only contain one value of each type.
*/

#ifndef META_SET_HPP_INCLUDED
#define META_SET_HPP_INCLUDED

#include <boost/mpl/pair.hpp>

#include <boost/utility/enable_if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/contains.hpp"
#include "meta/fold_reverse.hpp"

#include "meta/detail/key_value.hpp"

namespace meta {

    struct set_tag;

    template <class ... Types> class set;

    template <> class set<> {
    public:
        typedef set type;
    private:
        typedef key_value_detail::key_value_base index;

        template <class ... Types> friend class set;
        template <class Tag, class Direction> friend struct operation::contains;
    };

    template <class First, class ... Rest> class set <First, Rest ...> {
    public:
        typedef set type;
    private:
        typedef key_value_detail::key_value <First, First,
            typename set <Rest ...>::index> index;

        template <class ... Types> friend class set;
        template <class Tag, class Direction> friend struct operation::contains;
    };

    template <class ... Types> struct range_tag <set <Types ...> >
    { typedef set_tag type; };

    namespace operation {

        template <> struct default_direction <set_tag> {
            template <class Range> struct apply
            { typedef meta::front type; };
        };

        // empty.
        template <> struct empty <set_tag, front> {
            template <class Range, class Void = void> struct apply;

            template <class Void>
                struct apply <set<>, Void> : mpl::true_ {};
            template <class ... Types, class Void>
                struct apply <set <Types ...>, Void> : mpl::false_ {};
        };

        // size.
        template <> struct size <set_tag, front> {
            template <class Range> struct apply;

            template <class ... Types> struct apply <set <Types ...>>
            : mpl::size_t <sizeof ... (Types)> {};
        };

        // first.
        template <> struct first <set_tag, front> {
            template <class Set> struct apply;
            template <class FirstType, class ... Types>
                struct apply <set <FirstType, Types ...> >
            { typedef FirstType type; };
        };

        // drop.
        template <> struct drop_one <set_tag, front> {
            template <class Set> struct apply;

            template <class FirstType, class ... Types>
                struct apply <set <FirstType, Types ...> >
            { typedef set <Types ...> type; };
        };

        // push.
        template <> struct push <set_tag, front> {
            template <class NewElement, class Set> struct apply;

            template <class NewElement, class ... Types>
                struct apply <NewElement, set <Types ...> >
            { typedef set <NewElement, Types ...> type; };
        };

        // Specific to set:

        // contains.
        template <> struct contains <set_tag, front> {
            template <class Element, class Set> struct apply
            : key_value_detail::contains <Element, typename Set::index> {};
        };

        // insert.
        template <> struct insert <set_tag, front> {
            template <class NewElement, class Set> struct apply
            : mpl::eval_if <meta::contains <front, NewElement, Set>,
                mpl::identity <Set>,
                meta::push <front, NewElement, Set>> {};
        };

    } // namespace operation

    /**
    Turn any range into a set.
    The resulting set contains duplicate elements only once.
    */
    template <typename Direction, typename Sequence = void> struct as_set
    : fold_reverse <Direction,
        insert <front, mpl::_1, mpl::_2>, set<>, Sequence> {};

    template <typename Sequence> struct as_set <Sequence>
    : as_set <typename default_direction <Sequence>::type, Sequence> {};

    // A set can be straightforwardly converted; but a vector, for example,
    // must go through the normal route to remove duplicates.
    template <typename ... Types> struct as_set <front, set <Types ...> >
    { typedef set <Types ...> type; };

} // namespace meta


#endif  // META_SET_HPP_INCLUDED
