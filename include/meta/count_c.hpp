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

#ifndef META_COUNT_C_HPP_INCLUDED
#define META_COUNT_C_HPP_INCLUDED

#include <type_traits>

#include "vector_c.hpp"

namespace meta {

    /** \struct count_c
    Metafunction that returns a meta::size_t_vector with integers from \c begin
    to \c end-1.

    A value of this type can be used as an argument to a function to make it
    easy to extract indexed values from the function at compile time.

    This causes a number of instantiations in the order of the number of
    bits needed to represent \c end-begin.

    When count has already been instantiated for another length, the number of
    additional instantiations in in the order of the most significant bit that
    differs between the two values.

    \tparam begin (optional)
        The first value.
    \tparam end
        The past-the-end value.
    */
    template <std::size_t ... arguments> struct count_c;

    namespace count_c_detail {

        /**
        Compute the index of the first bit that is non-zero in \c operand.
        */
        template <std::size_t operand> struct highest_bit_index
        : std::integral_constant <std::size_t,
            highest_bit_index <(operand / 2)>::value + 1> {};

        template <> struct highest_bit_index <0>
        : std::integral_constant <std::size_t, 0> {};


        /**
        Contains a type <c>size_t_vector\<0, ..., 2**operand - 1></c>.

        The total number of instantiations across the program is \c O(operand)
        for the highest value of \c operand.
        */
        template <std::size_t operand> struct count_pow_2;

        template <class HalfResult> struct count_pow_2_impl;
        template <std::size_t ... half_result>
            struct count_pow_2_impl <size_t_vector <half_result ...>>
        {
            static constexpr std::size_t offset = sizeof... (half_result);
            typedef size_t_vector <half_result ..., half_result + offset ...>
                type;
        };

        template <> struct count_pow_2 <0> { typedef size_t_vector <0> type; };

        template <std::size_t operand> struct count_pow_2
        : count_pow_2_impl <typename count_pow_2 <(operand - 1)>::type> {};


        /**
        Concatenate size_t_vector types that contain counts from 0...N into a
        long size_t_vector with 0...N, with N the sum of all the original Ns.

        The total number of instantiations is optimised for repeated use with
        the same tail.
        */
        template <class ... Counts> struct concatenate_counts;

        template <> struct concatenate_counts<>
        { typedef size_t_vector<> type; };

        template <std::size_t ... counts1, std::size_t ... counts2>
            struct concatenate_counts <
                size_t_vector <counts1 ...>, size_t_vector <counts2 ...>>
        {
            static constexpr std::size_t offset = sizeof... (counts1);
            typedef size_t_vector <counts1 ..., (counts2 + offset) ...> type;
        };

        template <class Counts1> struct concatenate_counts <Counts1>
        { typedef Counts1 type; };

        // When CountsRest is the same between instantiations, the result is
        // reused.
        template <class Counts1, class ... CountsRest>
            struct concatenate_counts <Counts1, CountsRest ...>
        : concatenate_counts <Counts1,
            typename concatenate_counts <CountsRest ...>::type> {};

        /**
        Contain a type <c>size_t_vector\<0, ..., end - 1></c>.

        This causes a number of instantiations in the order of the number of
        bits needed to represent \c end.

        When count_from_zero has already been instantiated for another value,
        the number of additional instantiations in in the order of the most
        significant bit that differs between the two values.
        */
        template <std::size_t end> struct count_from_zero;

        template <std::size_t end, class bits> struct count_from_zero_impl;

        template <std::size_t end, std::size_t ... bits>
            struct count_from_zero_impl <end, size_t_vector <bits ...>>
        : concatenate_counts <
            typename std::conditional <bool (end & (std::size_t (1) << bits)),
                count_pow_2 <bits>, size_t_vector<>>::type::type
                ...>
        {
            static_assert ((end >> sizeof ... (bits)) == 0,
                "Internal error: number of bits computed is not sufficient.");
        };


        template <std::size_t end> struct count_from_zero
        : count_from_zero_impl <end,
            typename count_from_zero <highest_bit_index <end>::value>::type> {};

        template <> struct count_from_zero <0>
        { typedef size_t_vector<> type; };

        template <> struct count_from_zero <1>
        { typedef size_t_vector <0> type; };

        template <> struct count_from_zero <2>
        { typedef size_t_vector <0, 1> type; };

        /**
        Add offset \c offset to each of the values in \c Counts, which must be
        a size_t_vector.
        */
        template <class Counts, std::size_t offset> struct add_offset;

        template <std::size_t ... values, std::size_t offset>
            struct add_offset <size_t_vector <values ...>, offset>
        { typedef size_t_vector <(values + offset) ...> type; };

        /**
        Pass through \c Counts, but check that its length is equal to
        \c length.
        */
        template <class Counts, std::size_t length> struct check_length;

        template <std::size_t ... Counts, std::size_t length>
            struct check_length <size_t_vector <Counts ...>, length>
        {
            typedef size_t_vector <Counts ...> type;
            static_assert (sizeof ... (Counts) == length,
                "Internal error: "
                "the vector generated is not of the correct length.");
        };

    } // namespace count_c_detail

    template <std::size_t end> struct count_c <end>
    : count_c_detail::check_length <
        typename count_c_detail::count_from_zero <end>::type, end> {};

    template <std::size_t begin, std::size_t end> struct count_c <begin, end>
    : count_c_detail::check_length <typename count_c_detail::add_offset <
        typename count_c_detail::count_from_zero <(end - begin)>::type,
        begin>::type, (end - begin)> {};

} // namespace meta

#endif // META_COUNT_C_HPP_INCLUDED
