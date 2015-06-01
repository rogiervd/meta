/*
Copyright 2013 Rogier van Dalen.

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

#ifndef META_EMPTY_VIEW_HPP_INCLUDED
#define META_EMPTY_VIEW_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /** \struct empty_view
    Empty range.
    The direction of traversal can be specified; if not, it is "front".

    \tparam Direction The direction of traversal.
        If left out, front is used.
    */
    template <class Direction = front> struct empty_view {};

    template <class Direction> struct empty_view_tag;

    template <class Direction> struct range_tag <empty_view <Direction>>
    { typedef empty_view_tag <Direction> type; };

    namespace operation {

        template <class Direction>
            struct default_direction <empty_view_tag <Direction>>
        { template <class Range> struct apply { typedef Direction type; }; };

        template <class Direction>
            struct empty <empty_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::true_ {}; };

        template <class Direction>
            struct size <empty_view_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::size_t <0> {}; };

    } // namespace operation

} // namespace meta

#endif  // META_EMPTY_VIEW_HPP_INCLUDED

