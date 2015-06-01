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

#ifndef META_FLATTEN_HPP_INCLUDED
#define META_FLATTEN_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/fold.hpp"
#include "meta/concatenate.hpp"
#include "meta/vector.hpp"

#include <boost/mpl/placeholders.hpp>

namespace meta {

    template <typename Direction, typename Sequences = void> struct flatten;

    template <typename Sequences> struct flatten <Sequences>
    : flatten <typename default_direction <Sequences>::type, Sequences> {};

    namespace flatten_detail {

        // Implementation: depends on whether Sequences is empty.
        template <typename Direction, typename Sequences,
                bool Empty = meta::empty <Direction, Sequences>::value>
            struct flatten;

        template <typename Direction, typename Sequences>
            struct flatten <Direction, Sequences, true>
        {
            typedef Sequences type;
        };

        template <typename Direction, typename Sequences>
            struct flatten <Direction, Sequences, false>
        : fold <Direction, meta::concatenate <mpl::_, mpl::_>,
            Sequences> {};

    } // namespace flatten_detail

    template <typename Direction, typename Sequences>
        struct flatten
    : flatten_detail::flatten <Direction, Sequences> {};

} // namespace meta

#endif  // META_FLATTEN_HPP_INCLUDED

