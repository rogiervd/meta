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

#ifndef META_EQUAL_HPP_INCLUDED
#define META_EQUAL_HPP_INCLUDED

#include <type_traits>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>

namespace meta {

    template <typename Direction, typename Predicate,
            typename Range1 = void, typename Range2 = void>
        struct equal;

    template <typename Predicate, typename Range1, typename Range2>
        struct equal <Predicate, Range1, Range2,
            typename boost::disable_if <is_direction <Predicate> >::type>
    : equal <typename default_direction <Range1>::type,
        Predicate, Range1, Range2> {};

    template <typename Direction, typename Range1, typename Range2>
        struct equal <Direction, Range1, Range2,
            typename boost::enable_if <is_direction <Direction> >::type>
    : equal <Direction, std::is_same <mpl::_, mpl::_>, Range1, Range2>
    {};

    template <typename Direction, typename Predicate,
            typename Range1, typename Range2>
        struct equal_impl
    : mpl::eval_if <
        typename mpl::apply <Predicate,
            typename first <Direction, Range1>::type,
            typename first <Direction, Range2>::type
        >::type,
        equal <Direction,
            typename drop <Direction, Range1>::type,
            typename drop <Direction, Range2>::type
        >,
        mpl::false_
    > {};

    template <typename Direction, typename Predicate,
            typename Range1, typename Range2>
        struct equal
    : mpl::eval_if <
        mpl::and_ <empty <Direction, Range1>, empty <Direction, Range2> >,
        // Both empty
        mpl::true_,
        mpl::eval_if <
            mpl::or_ <empty <Direction, Range1>, empty <Direction, Range2> >,
            // One empty
            mpl::false_,
            equal_impl <Direction, Predicate, Range1, Range2>
        >
    > {};

} // namespace meta

#endif  // META_EQUAL_HPP_INCLUDED

