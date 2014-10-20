/*
Copyright 2014 Rogier van Dalen.

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

/* \file
Look up a type-index element in a list.
Sets, maps, multisets and multimaps can be based on this.

This is currently a linear structure.
It could be turned into a binary tree, so that insert and remove take
logarithmic time
This, however, would require a balanced tree, which may be more effort than
reasonable.
*/

#ifndef META_DETAIL_KEY_VALUE_HPP_INCLUDED
#define META_DETAIL_KEY_VALUE_HPP_INCLUDED

#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>

#include "../fold.hpp"

namespace meta { namespace key_value_detail {

    struct not_found {};
    template <class Key, class Index> struct get_value_wrapper;
    template <class Key, class Index,
            class Wrapper = typename get_value_wrapper <Key, Index>::type
        > struct contains;

    template <class Key> struct wrapper {
        typedef Key type;
    };

    struct key_value_base {
        template <class Key> static not_found find (wrapper <Key>);
    };

    template <class Key, class Value, class Base> struct key_value
    : Base {
        static_assert (!contains <Key, Base>::value,
            "Key can only be in index once.");

        using Base::find;

        static wrapper <Value> find (wrapper <Key>);
    };

    template <class Key, class Index> struct get_value_wrapper
    { typedef decltype (Index::find (wrapper <Key>())) type; };

    /**
    Return whether the index contains the key.
    */
    template <class Key, class Index, class Wrapper
        /*= typename get_value_wrapper <Key, Index>::type*/>
        struct contains;

    template <class Key, class Index>
        struct contains <Key, Index, not_found>
    : mpl::false_ {};

    template <class Key, class Index, class Value>
        struct contains <Key, Index, wrapper <Value>>
    : mpl::true_ {};

    /**
    Return value for key from index.
    \pre The value is actually in the index.
    */
    template <class Key, class Index,
            class Wrapper = typename get_value_wrapper <Key, Index>::type
        > struct value;

    template <class Key, class Index, class Value>
        struct value <Key, Index, wrapper <Value>>
    { typedef Value type; };

    /**
    Return value for key from index, or IfNotFound if the key is not found.
    */
    template <class Key, class IfNotFound, class Index,
            class Wrapper = typename get_value_wrapper <Key, Index>::type
        > struct value_or;

    template <class Key, class IfNotFound, class Index>
        struct value_or <Key, IfNotFound, Index, not_found>
    { typedef IfNotFound type; };

    template <class Key, class IfNotFound, class Index, class Value>
        struct value_or <Key, IfNotFound, Index, wrapper <Value>>
    { typedef Value type; };

    /**
    Remove key from index.
    */
    template <class Key, class Index> struct remove;

    // Found.
    template <class Key, class Value, class Base>
        struct remove <Key, key_value <Key, Value, Base>>
    { typedef Base type; };

    // Not found.
    template <class TargetKey, class FirstKey, class Value, class Base>
        struct remove <TargetKey, key_value <FirstKey, Value, Base>>
    {
        typedef key_value <FirstKey, Value,
            typename remove <TargetKey, Base>::type> type;
    };

    /**
    Insert key in index.
    */
    template <class Key, class Value, class Index> struct insert {
        static_assert (!contains <Key, Index>::value,
            "Index already contains key.");

        typedef key_value <Key, Value, Index> type;
    };

    /**
    Make an index type that consists of a string of key_value types.
    The input KeyValuePairs is a meta-range of mpl::pair's.
    */
    template <class KeyValuePairs> struct make_index {
        typedef typename fold <
            key_value_detail::key_value <
                mpl::first <mpl::_2>, mpl::second <mpl::_2>, mpl::_1>,
            key_value_detail::key_value_base,
            KeyValuePairs>::type type;
    };

}} // namespace meta::key_value_detail

#endif // META_DETAIL_KEY_VALUE_HPP_INCLUDED
