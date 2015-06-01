/*
Copyright 2011, 2012, 2014, 2015 Rogier van Dalen.

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
#include "meta/all_of_c.hpp"

#include "meta/detail/index.hpp"

namespace meta {

    struct set_tag;

    template <class Type> struct set_element { typedef Type key; };

    template <class ... Types> class set {
    public:
        typedef set type;

        typedef index_detail::index <set_element <Types> ...> index;
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

        struct find_in_set {
            template <class Element, class Set> struct apply
            : index_detail::contains <Element, typename Set::index> {};
        };

        // contains.
        template <> struct contains <set_tag, front> : find_in_set {};
        template <> struct has_key <set_tag> : find_in_set {};

        // insert.
        template <> struct insert <set_tag, front> {
            template <class NewElement, class Set> struct apply
            : mpl::eval_if <meta::contains <front, NewElement, Set>,
                mpl::identity <Set>,
                meta::push <front, NewElement, Set>> {};
        };

        // remove.
        template <> struct remove <set_tag> {
            template <class Key, class Set> struct apply {
                typedef typename index_detail::remove <Key, typename Set::index
                    >::type new_index;

                template <class Index> struct get_set;
                template <class ... Entries>
                    struct get_set <index_detail::index <Entries ...>>
                { typedef set <typename Entries::key ...> type; };

                typedef typename get_set <new_index>::type type;
            };
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

    /** \brief
    Evaluate to \c true iff \a Subset is a subset of \a Superset, that is, iff
    \a Superset contains all elements of \a Subset.

    This causes O(n) template instantiations.
    */
    template <class Subset, class Superset> struct is_subset;

    template <class ... Elements, class Superset>
        struct is_subset <set <Elements ...>, Superset>
    : all_of_c <contains <Elements, Superset>::value ...> {};

} // namespace meta

#endif  // META_SET_HPP_INCLUDED
