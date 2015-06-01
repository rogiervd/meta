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

#ifndef META_CONTAINS_HPP_INCLUDED
#define META_CONTAINS_HPP_INCLUDED

#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/not.hpp>

#include "meta/range.hpp"
#include "meta/find.hpp"

namespace meta {

    /**
    Shorthand for not_ <empty <find <is_same <Type, _>, Range> > >.

    This causes O(n) instantiations with n the length of the range or the first
    position of Type.
    This may be optimised for a specific container type.
    */
    template <class Direction, class Type, class Range = void>
        struct contains;

    template <class Type, class Range>
        struct contains <Type, Range>
    : contains <typename default_direction <Range>::type, Type, Range> {};

    template <class Direction, class Type, class Range>
        struct contains
    : operation::contains <typename range_tag <Range>::type, Direction>
        ::template apply <Type, Range> {};

    namespace operation {

        template <class Tag, class Direction> struct contains {
            template <class Type, class Range> struct apply
            : mpl::not_ <meta::empty <Direction, typename meta::find <
                Direction, std::is_same <Type, mpl::_>, Range>::type>> {};
        };

    } // namespace operation

} // namespace meta

#endif  // META_CONTAINS_HPP_INCLUDED

