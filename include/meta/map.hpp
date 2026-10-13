// SPDX-FileCopyrightText: Copyright 2011, 2012, 2014, 2015 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

/** \file
Define meta::map, an MPL sequence that maps types to other types.
*/

#ifndef META_MAP_HPP_INCLUDED
#define META_MAP_HPP_INCLUDED

#include <boost/mpl/pair.hpp>

#include <boost/utility/enable_if.hpp>

#include "meta/contains.hpp"
#include "meta/fold_reverse.hpp"
#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include "meta/detail/index.hpp"

namespace meta {

struct map_tag;

template <class Key, class Value> struct map_element
{
    typedef Key key;
    typedef Value value;
};

template <class... Types> class map;

template <class... Keys, class... Values>
class map<map_element<Keys, Values>...>
{
public:
    typedef map type;

    typedef index_detail::index<map_element<Keys, Values>...> index;
};

template <class... Types> struct range_tag<map<Types...>>
{
    typedef map_tag type;
};

namespace operation {

    template <> struct default_direction<map_tag>
    {
        template <class Range> struct apply
        {
            typedef meta::front type;
        };
    };

    // empty.
    template <> struct empty<map_tag, front>
    {
        template <class Range, class Void = void> struct apply;

        template <class Void> struct apply<map<>, Void> : mpl::true_ {};
        template <class... Types, class Void> struct apply<map<Types...>, Void>
        : mpl::false_ {};
    };

    // size.
    template <> struct size<map_tag, front>
    {
        template <class Range> struct apply;

        template <class... Types> struct apply<map<Types...>>
        : mpl::size_t<sizeof...(Types)> {};
    };

    // first.
    template <> struct first<map_tag, front>
    {
        template <class Map> struct apply;
        template <class FirstType, class... Types>
        struct apply<map<FirstType, Types...>>
        {
            typedef FirstType type;
        };
    };

    // drop.
    template <> struct drop_one<map_tag, front>
    {
        template <class Map> struct apply;

        template <class FirstType, class... Types>
        struct apply<map<FirstType, Types...>>
        {
            typedef map<Types...> type;
        };
    };

    // push.
    template <> struct push<map_tag, front>
    {
        template <class NewElement, class Map> struct apply;

        template <class NewElement, class... Types>
        struct apply<NewElement, map<Types...>>
        {
            typedef map<NewElement, Types...> type;
        };
    };

    // Specific to map:

    // has_key.
    template <> struct has_key<map_tag>
    {
        template <class Key, class Map> struct apply
        : index_detail::contains<Key, typename Map::index> {};
    };

    // at.
    template <> struct at<map_tag>
    {
        template <class Key, class Map> struct apply
        {
            typedef typename index_detail::find_entry<
                Key, typename Map::index>::type::value type;
        };
    };

    // insert.
    template <class Index> struct index_to_map;

    template <class... Entries>
    struct index_to_map<index_detail::index<Entries...>>
    {
        typedef map<Entries...> type;
    };

    template <> struct insert<map_tag, front>
    {
        template <class NewElement, class Map> struct apply
        : index_to_map<typename index_detail::insert<
              NewElement, typename Map::index>::type> {};
    };

    // remove.
    template <> struct remove<map_tag>
    {
        template <class Key, class Map> struct apply
        : index_to_map<
              typename index_detail::remove<Key, typename Map::index>::type> {};
    };

}  // namespace operation

}  // namespace meta

#endif  // META_MAP_HPP_INCLUDED
