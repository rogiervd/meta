/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

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

#ifndef META_FILTER_HPP_INCLUDED
#define META_FILTER_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace meta
{
    template <typename Direction, typename Predicate, typename Range /*= void*/>
        struct filter;

    template <typename Predicate, typename Range>
        struct filter <Predicate, Range>
    : filter <typename default_direction <Range>::type, Predicate, Range> {};

    namespace detail
    {
        template <typename Direction, typename Predicate, typename Range,
                bool Empty = meta::empty <Direction, Range>::value>
            struct filter;

        template <typename Direction, typename Predicate, typename Range>
            struct filter <Direction, Predicate, Range, true>
        {
            typedef Range type;
        };

        template <typename Direction, typename Predicate, typename Range>
            struct filter <Direction, Predicate, Range, false>
        {
            typedef typename first <Direction, Range>::type head;
            typedef typename drop <Direction, Range>::type tail;
            typedef typename filter <Direction, Predicate, tail>::type filtered_tail;
            typedef typename mpl::eval_if <
                    typename mpl::apply <Predicate, head>::type,
                    push <Direction, head, filtered_tail>,
                    mpl::identity <filtered_tail>
                >::type type;
        };
    }   // namespace detail

    template <typename Direction, typename Predicate, typename Range>
        struct filter
    : detail::filter <Direction, Predicate, Range> {};

}   // namespace meta

#endif  // META_FILTER_HPP_INCLUDED

