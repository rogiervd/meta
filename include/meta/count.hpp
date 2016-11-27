/*
Copyright 2014, 2015 Rogier van Dalen.

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

#ifndef META_COUNT_HPP_INCLUDED
#define META_COUNT_HPP_INCLUDED

#include <type_traits>

#include "meta/range.hpp"
#include "meta/vector.hpp"

#include "count_c.hpp"

namespace meta {

    /** \struct count
    Metafunction that returns a \a meta::vector of integral constants with
    increasing value.
    The constants are \a std::integral_constant with type \a std::size_t.
    Thus, <c>count\<1,3>::type</c> is
    <c>meta::vector\<std::integral_constant\<1>,std::integral_constant\<2>></c>.

    It is specified exactly that the result is a meta::vector with elements that
    are \a std::integral_constant.
    This facilitates a common trick.
    This can be useful for use in argument pack expansion.
    You can call a function with <c>count\<2,4>::type()</c> as an argument, and
    pattern match on \c meta::vector\<Counts...>.
    Then,
    <c>std::get \<Counts::value> (tuple) ...</c>
    will expand to
    <c>std::get \<2> (tuple), std::get \<3> (tuple), std::get \<4> (tuple)</c>.
    This allows one to extract a sequence of elements from a \c std::tuple and
    pass them as arguments to a function.
    The unit test in ../../test/meta/test-count.cpp has two examples of this
    sort of trick.

    \tparam begin
        The value of the first element.
        If this is left out, 0 is assumed.
    \tparam end The value of the one-past-last element.

    \sa count_c
    */
    template <std::size_t ... arguments> struct count;

    namespace count_detail {

        template <class Values> struct make_integral_constants;

        template <std::size_t ... values>
            struct make_integral_constants <size_t_vector <values ...>>
        : meta::vector <std::integral_constant <std::size_t, values> ...> {};

    } // namespace count_detail

    template <std::size_t ... Arguments> struct count
    : count_detail::make_integral_constants <
        typename count_c <Arguments ...>::type> {};

} // namespace meta

#endif // META_COUNT_HPP_INCLUDED
