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

#ifndef META_FLATTEN_HPP_INCLUDED
#define META_FLATTEN_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/fold.hpp"
#include "meta/concatenate.hpp"
#include "meta/vector.hpp"

#include <boost/mpl/placeholders.hpp>

namespace meta
{
    template <typename Direction, typename Sequences /*= void*/> struct flatten;

    template <typename Sequences> struct flatten <Sequences>
    : flatten <typename default_direction <Sequences>::type, Sequences> {};

    namespace flatten_detail
    {
        // Implementation: depends on whether Sequences is empty.
        template <typename Direction, typename Sequences,
                bool Empty = meta::empty <Direction, Sequences>::value>
            struct flatten;

        template <typename Direction, typename Sequences>
            struct flatten <Direction, Sequences, true>
        {
            typedef Sequences type;
        };

        template <typename Direction, typename Sequences>
            struct flatten <Direction, Sequences, false>
        : fold <Direction, meta::concatenate <mpl::_, mpl::_>,
            Sequences> {};

    }   // namespace flatten_detail

    template <typename Direction, typename Sequences>
        struct flatten
    : flatten_detail::flatten <Direction, Sequences> {};

}   // namespace meta

#endif  // META_FLATTEN_HPP_INCLUDED

