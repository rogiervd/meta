/*
Copyright 2014, 2015 Rogier van Dalen.

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

/* \file
Look up a type-index element in an index.
Associative containers can be built on top of this.

Queries cost O(1) instantiations.
*/

#ifndef META_DETAIL_INDEX_HPP_INCLUDED
#define META_DETAIL_INDEX_HPP_INCLUDED

#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>

#include "../vector.hpp"

namespace meta { namespace index_detail {

    template <class ... Keys> class index;
    template <class Key, class Value> struct key_value;
    template <class Key, class Index> struct contains;

    struct not_found {};

    template <class Key> struct pass_key {
        typedef Key type;
    };

    template <> class index<> {
    public:
        template <class Key> static not_found find (pass_key <Key>);
    };

    template <class Entry, class ... Rest> class index <Entry, Rest ...>
    : Entry, index <Rest ...> {
    private:
        typedef index <Rest ...> rest_index;

        typedef typename Entry::key entry_key;

        static_assert (!contains <entry_key, rest_index>::value,
            "Key can only be in index once.");

    public:
        using rest_index::find;
        static Entry find (pass_key <entry_key>);

        /// Return the index without the entry with key \a Key
        template <class Key, class ... PreviousEntries> struct remove
        : rest_index::template remove <Key, PreviousEntries ..., Entry> {};

        template <class ... PreviousEntries>
            struct remove <entry_key, PreviousEntries ...>
        { typedef index <PreviousEntries ..., Rest ...> type; };
    };

    template <class Key, class Index> struct find_entry {
        typedef decltype (Index::find (pass_key <Key>())) type;
    };

    /** \brief
    Return whether the index contains the key.

    This results in O(1) instantiations.
    */
    template <class Key, class Index> struct contains
    : boost::mpl::not_ <
        std::is_same <typename find_entry <Key, Index>::type, not_found>> {};

    /** \brief
    Return the index with the entry with key \a Key removed.

    This results in O(n) instantiations where n is the position of the element
    in the index.
    */
    template <class Key, class Index> struct remove
    : Index::template remove <Key> {};

    /** \brief
    Add entry \a Entry to index \a Index.

    This results in O(1) instantiations.

    \pre The index must not yet contain an entry with this key.
    */
    template <class Entry, class Index> struct push_front;

    template <class Entry, class ... Entries>
        struct push_front <Entry, index <Entries ...>>
    {
        static_assert (
            !contains <typename Entry::key, index <Entries ...>>::value,
            "Key must not already be in this index.");
        typedef index <Entry, Entries ...> type;
    };

    /* insert. */
    template <class Entry, class Index, bool key_exists>
        struct insert_implementation
    : push_front <Entry, Index> {};

    template <class Entry, class Index>
        struct insert_implementation <Entry, Index, true>
    : push_front <Entry, typename remove <typename Entry::key, Index>::type> {};

    /**
    Add entry \a Entry to \a Index, replacing any old entry with the same key.

    This results in O(n) instantiations where n is the position of the element
    in the index, or O(1) instantiations if the element is not yet in the index.
    */
    template <class Entry, class Index> struct insert
    : insert_implementation <Entry, Index,
        contains <typename Entry::key, Index>::value> {};

}} // namespace meta::index_detail

#endif // META_DETAIL_INDEX_HPP_INCLUDED
