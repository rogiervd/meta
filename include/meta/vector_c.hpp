// SPDX-FileCopyrightText: Copyright 2015 Rogier van Dalen
//
// SPDX-License-Identifier: Apache-2.0

#ifndef META_VECTOR_C_HPP_INCLUDED
#define META_VECTOR_C_HPP_INCLUDED

#include <cstddef>

namespace meta {

/** \struct vector_c
Compile-time vector with values of one fixed type.

This does not currently behave as a Range.
(But that could be added later.)

This is useful to pass into a function which can deduce it in parameter
pack expansion.
*/
template <class Type, Type... Values> struct vector_c
{
    typedef vector_c type;
};

template <std::size_t... Values> using size_t_vector =
    vector_c<std::size_t, Values...>;

}  // namespace meta

#endif  // META_VECTOR_C_HPP_INCLUDED
