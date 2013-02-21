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

/**
Declarations of directions of iteration through ranges.

The ones declared here are just compile-time, so they can be used to iterate
through compile-time sequences.
In ../range/direction.hpp, this is extended to run-time sequences.
*/

#ifndef RANGE_DIRECTION_TAG_HPP_INCLUDED
#define RANGE_DIRECTION_TAG_HPP_INCLUDED

#include <type_traits>

#include <boost/mpl/bool.hpp>

namespace direction {

/**
Metafunction that returns true iff Direction is a direction.
Direction may not be const-qualified or a reference.

Specialise this for user-defined direction classes.
*/
template <class Direction, class Enable = void>
    struct is_direction_bare : boost::mpl::false_ {};

/**
Metafunction that returns true iff Direction is a direction.
Direction may be const-qualified and/or a reference.

Specialise is_direction_bare for user-defined direction classes.
*/
template <class Direction> struct is_direction
: is_direction_bare <typename std::decay <Direction>::type> {};

/* Predefined directions */

// These are also used for run-time ranges.
// Their definitions are in ../range/direction.hpp.
struct front;
struct back;

template <> struct is_direction_bare <direction::front>
: boost::mpl::true_ {};
template <> struct is_direction_bare <direction::back>
: boost::mpl::true_ {};

} // namespace direction

#endif  // RANGE_DIRECTION_TAG_HPP_INCLUDED

