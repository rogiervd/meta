/*
Copyright 2011, 2012 Rogier van Dalen.

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

#ifndef META_CONTAINS_HPP_INCLUDED
#define META_CONTAINS_HPP_INCLUDED

#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/not.hpp>

#include "meta/range.hpp"
#include "meta/find.hpp"

namespace meta {

    /**
    Shorthand for not_ <empty <find <is_same <Type, _>, Range> > >.
    \todo Add predicated version?
    Or does that not make sense since this is a shorthand, really?
    */
    template <typename Direction, typename Type, typename Range = void>
        struct contains;

    template <typename Type, typename Range>
        struct contains <Type, Range>
    : contains <typename default_direction <Range>::type, Type, Range> {};

    template <typename Direction, typename Type, typename Range>
        struct contains
    : mpl::not_ <empty <Direction, typename find <
        Direction, std::is_same <Type, mpl::_>, Range>::type> > {};

} // namespace meta

#endif  // META_CONTAINS_HPP_INCLUDED

