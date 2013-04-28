/*
Copyright 2013 Rogier van Dalen.

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

#ifndef META_ALL_HPP_INCLUDED
#define META_ALL_HPP_INCLUDED

#include <boost/mpl/if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Return true iff all elements in Range are true.
    If Range is empty, also return true.
    Direction can be left out.
    */
    template <typename Direction, typename Range = void> struct all;

    template <typename Range> struct all <Range>
    : all <typename default_direction <Range>::type, Range> {};

    namespace implementation {
        template <typename Direction, typename Range> struct all_non_empty
        : mpl::if_ <typename first <Direction, Range>::type,
            meta::all <Direction, typename drop <Direction, Range>::type>,
            mpl::false_>::type {};
    } // namespace implementation

    template <typename Direction, typename Range> struct all
    : mpl::if_ <empty <Direction, Range>,
        mpl::true_, implementation::all_non_empty <Direction, Range>>::type {};

} // namespace meta

#endif  // META_ALL_HPP_INCLUDED

