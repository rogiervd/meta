/*
Copyright 2013 Rogier van Dalen.

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

#ifndef META_MERGE_HPP_INCLUDED
#define META_MERGE_HPP_INCLUDED

#include <type_traits>

#include <boost/utility/enable_if.hpp>

#include <boost/mpl/less.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/identity.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /** \struct merge
    Lazily merge two sorted sequences into one sorted sequence.
    This causes a constant number of instantiations for all operations.

    \tparam Direction The direction in which the sort order is defined.
        Left and Right are traversed in this direction.
        \c default_direction<Left> is used if this is left out.
    \tparam Compare The ordering meta-function.
        \c mpl::less is used if this is left out.
    \tparam Left A range.
    \tparam Right Another range.
    */
    template <class Direction, class Compare,
            class Left = void, class Right = void>
        struct merge;

    // Only direction: insert mpl::less <...>.
    template <class Direction, class Left, class Right>
        struct merge <Direction, Left, Right,
            typename boost::enable_if <is_direction <Direction>>::type>
    : merge <Direction, mpl::less <mpl::_1, mpl::_2>, Left, Right> {};

    // Only Compare: insert default direction.
    template <class Compare, class Left, class Right>
        struct merge <Compare, Left, Right,
            typename boost::disable_if <boost::mpl::or_ <
                is_direction <Compare>, std::is_same <Right, void>>>::type>
    : merge <typename default_direction <Left>::type, Compare, Left, Right> {};

    // No parameters: insert default direction.
    template <class Left, class Right> struct merge <Left, Right>
    : merge <typename default_direction <Left>::type, Left, Right> {};

    namespace merge_detail {

        // Simple base class for if both ranges are empty.
        template <class Direction> struct empty_merge
        { typedef mpl::true_ empty; };

        // Is the left range first?
        // Assumes Left and Right are non-empty.
        template <class Direction, class Compare, class Left, class Right>
            struct left_first
        : mpl::apply <Compare,
            typename meta::first <Direction, Left>::type,
            typename meta::first <Direction, Right>::type>::type {};

        // Is the left range first?
        // Assumes either Left or Right is non-empty.
        template <class Direction, class Compare, class Left, class Right>
            struct favourite
        : mpl::eval_if <empty <Direction, Left>, mpl::false_,
            mpl::eval_if <empty <Direction, Right>, mpl::true_,
            left_first <Direction, Compare, Left, Right>>>::type {};

        // Base class for if at least one of the ranges is non-empty.
        template <class Direction, class Compare, class Left, class Right>
            struct non_empty_merge
        {
            typedef mpl::false_ empty;
            typedef favourite <Direction, Compare, Left, Right> left_bound;
        };

    } // namespace merge_detail

    // Forward to the appropriate base class in merge_detail.
    template <class Direction, class Compare, class Left, class Right>
        struct merge
    : mpl::if_ <
        mpl::and_ <empty <Direction, Left>, empty <Direction, Right>>,
        merge_detail::empty_merge <Direction>,
        merge_detail::non_empty_merge <Direction, Compare, Left, Right>>::type
    {
        static_assert (is_range <Left>::value, "Left must be a range");
        static_assert (is_range <Right>::value, "Left must be a range");
        // When template arguments are left out, this implementation is the
        // base class.
        // The following definitions normalise the information in the arguments.
        typedef merge type;

        typedef Direction direction;
        typedef Compare compare;
        typedef Left left;
        typedef Right right;
    };

    template <class Direction> struct merge_tag;

    template <class Direction, class Compare, class Left, class Right>
        struct range_tag <merge <Direction, Compare, Left, Right>>
    {
        typedef merge_tag <
            typename merge <Direction, Compare, Left, Right>::direction> type;
    };

    namespace operation {

        // default_direction.
        template <class Direction>
            struct default_direction <merge_tag <Direction>>
        { template <class Range> struct apply { typedef Direction type; }; };

        // empty.
        template <class Direction>
            struct empty <merge_tag <Direction>, Direction>
        { template <class Range> struct apply : Range::empty {}; };

        // size: not implemented.

        // first.
        template <class Direction>
            struct first <merge_tag <Direction>, Direction>
        {
            template <class Range> struct apply
            : mpl::eval_if <typename Range::left_bound,
                meta::first <typename Range::direction, typename Range::left>,
                meta::first <typename Range::direction, typename Range::right>>
            {};
        };

        // drop_one.
        template <class Direction>
            struct drop_one <merge_tag <Direction>, Direction>
        {
            template <class Range> struct apply {
                typedef merge <typename Range::direction,
                    typename Range::compare,
                    // Drop from left if we are left-bound.
                    typename mpl::eval_if <typename Range::left_bound,
                        meta::drop <typename Range::direction,
                            typename Range::left>,
                        mpl::identity <typename Range::left>
                    >::type,
                    // If not, drop from right.
                    typename mpl::eval_if <
                        mpl::not_ <typename Range::left_bound>,
                        meta::drop <typename Range::direction,
                            typename Range::right>,
                        mpl::identity <typename Range::right>
                    >::type> type;
            };
        };

    } // namespace operation

} // namespace meta

#endif // META_MERGE_HPP_INCLUDED

