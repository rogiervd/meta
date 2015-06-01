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

