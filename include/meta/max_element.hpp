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

#ifndef META_MAX_ELEMENT_HPP
#define META_MAX_ELEMENT_HPP

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/fold.hpp"

namespace meta {

    template <typename Direction, typename Range = void> struct max_element;

    template <typename Range> struct max_element <Range>
    : max_element <typename default_direction <Range>::type, Range> {};

    namespace max_element_detail {
        struct max_of_two {
            // If we were to use mpl::max here, it would refuse to work with
            // std::integral_constant, because it lacks tags that Boost.MPL
            // expects.
            template <typename First, typename Second,
                bool less = (First::value < Second::value)> struct apply;

            template <typename First, typename Second>
                struct apply <First, Second, true> : Second {};
            template <typename First, typename Second>
                struct apply <First, Second, false> : First {};
        };
    } // namespace max_element_detail

    template <typename Direction, typename Range>
        struct max_element
    : fold <Direction, max_element_detail::max_of_two, Range> {};

} // namespace meta

#endif  // META_MAX_ELEMENT_HPP

