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

#ifndef META_MAX_ELEMENT_HPP
#define META_MAX_ELEMENT_HPP

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/fold.hpp"

namespace meta {

    template <typename Direction, typename Range = void> struct max_element;

    template <typename Range> struct max_element <Range>
    : max_element <typename default_direction <Range>::type, Range> {};

    namespace max_element_detail {
        struct max_of_two {
            // If we were to use mpl::max here, it would refuse to work with
            // std::integral_constant, because it lacks tags that Boost.MPL
            // expects.
            template <typename First, typename Second,
                bool less = (First::value < Second::value)> struct apply;

            template <typename First, typename Second>
                struct apply <First, Second, true> : Second {};
            template <typename First, typename Second>
                struct apply <First, Second, false> : First {};
        };
    } // namespace max_element_detail

    template <typename Direction, typename Range>
        struct max_element
    : fold <Direction, max_element_detail::max_of_two, Range> {};

} // namespace meta

#endif  // META_MAX_ELEMENT_HPP

