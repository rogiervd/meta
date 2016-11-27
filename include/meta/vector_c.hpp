/*
Copyright 2015 Rogier van Dalen.

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
    template <class Type, Type ... Values> struct vector_c
    { typedef vector_c type; };

    template <std::size_t ... Values>
        using size_t_vector = vector_c <std::size_t, Values...>;

} // namespace meta

#endif // META_VECTOR_C_HPP_INCLUDED
