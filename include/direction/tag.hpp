// SPDX-FileCopyrightText: Copyright 2011, 2012 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

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
template <class Direction, class Enable = void> struct is_direction_bare
: boost::mpl::false_ {};

/**
Metafunction that returns true iff Direction is a direction.
Direction may be const-qualified and/or a reference.

Specialise is_direction_bare for user-defined direction classes.
*/
template <class Direction> struct is_direction
: is_direction_bare<typename std::decay<Direction>::type> {};

/* Predefined directions */

// These are also used for run-time ranges.
// Their definitions are in ../range/direction.hpp.
struct front;
struct back;

template <> struct is_direction_bare<direction::front> : boost::mpl::true_ {};
template <> struct is_direction_bare<direction::back> : boost::mpl::true_ {};

}  // namespace direction

#endif  // RANGE_DIRECTION_TAG_HPP_INCLUDED
