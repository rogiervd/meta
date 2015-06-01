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

#ifndef META_ALL_OF_C_HPP_INCLUDED
#define META_ALL_OF_C_HPP_INCLUDED

#include <type_traits>

namespace meta {

    /**
    Return true iff all arguments are true.
    If no arguments are given, also return true.

    This is less generic than \ref all_of, which works on all types of ranges,
    but it causes fewer template instantiations, so it improves compile speed
    and memory use.
    */
    template <bool ...> struct all_of_c;

    template <> struct all_of_c<> : std::true_type {};

    template <bool value1> struct all_of_c <value1>
    : std::integral_constant <bool, value1> {};

    template <bool value1, bool value2>
        struct all_of_c <value1, value2>
    : std::integral_constant <bool, value1 && value2> {};

    template <bool value1, bool value2, bool value3>
        struct all_of_c <value1, value2, value3>
    : std::integral_constant <bool, value1 && value2 && value3> {};

    template <bool value1, bool value2, bool value3, bool value4>
        struct all_of_c <value1, value2, value3, value4>
    : std::integral_constant <bool, value1 && value2 && value3 && value4> {};

    template <bool value1, bool value2, bool value3, bool value4, bool ... rest>
        struct all_of_c <value1, value2, value3, value4, rest ...>
    : std::integral_constant <bool, value1 && value2 && value3 && value4 &&
        all_of_c <rest ...>::value> {};

} // namespace meta

#endif // META_ALL_OF_C_HPP_INCLUDED
