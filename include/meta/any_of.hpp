/*
Copyright 2013, 2015 Rogier van Dalen.

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

#ifndef META_ANY_OF_HPP_INCLUDED
#define META_ANY_OF_HPP_INCLUDED

#include <boost/mpl/if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Return true iff any element in Range is true.
    If Range is empty, then return false.
    Direction can be left out.
    */
    template <typename Direction, typename Range = void> struct any_of;

    template <typename Range> struct any_of <Range>
    : any_of <typename default_direction <Range>::type, Range> {};

    namespace implementation {
        template <typename Direction, typename Range> struct any_of_non_empty
        : mpl::if_ <typename first <Direction, Range>::type,
            mpl::true_,
            meta::any_of <Direction, typename drop <Direction, Range>::type>
            >::type {};
    } // namespace implementation

    template <typename Direction, typename Range> struct any_of
    : mpl::if_ <empty <Direction, Range>,
        mpl::false_, implementation::any_of_non_empty <Direction, Range>>::type
    {};

} // namespace meta

#endif // META_ANY_OF_HPP_INCLUDED
