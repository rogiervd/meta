/*
Copyright 2015 Rogier van Dalen.

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

#ifndef META_ANY_OF_C_HPP_INCLUDED
#define META_ANY_OF_C_HPP_INCLUDED

#include <type_traits>

namespace meta {

    /**
    Return true iff all arguments are true.
    If no arguments are given, also return true.

    This is less generic than \ref any_of, which works on all types of ranges,
    but it causes fewer template instantiations, so it improves compile speed
    and memory use.
    */
    template <bool ...> struct any_of_c;

    template <> struct any_of_c<> : std::false_type {};

    template <bool value1> struct any_of_c <value1>
    : std::integral_constant <bool, value1> {};

    template <bool value1, bool value2>
        struct any_of_c <value1, value2>
    : std::integral_constant <bool, value1 || value2> {};

    template <bool value1, bool value2, bool value3>
        struct any_of_c <value1, value2, value3>
    : std::integral_constant <bool, value1 || value2 || value3> {};

    template <bool value1, bool value2, bool value3, bool value4>
        struct any_of_c <value1, value2, value3, value4>
    : std::integral_constant <bool, value1 || value2 || value3 || value4> {};

    template <bool value1, bool value2, bool value3, bool value4, bool ... rest>
        struct any_of_c <value1, value2, value3, value4, rest ...>
    : std::integral_constant <bool, value1 || value2 || value3 || value4 ||
        any_of_c <rest ...>::value> {};

} // namespace meta

#endif // META_ANY_OF_C_HPP_INCLUDED
