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

#ifndef META_CONCATENATE_HPP_INCLUDED
#define META_CONCATENATE_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    /**
    Concatenate two ranges.
    This means that Range1 is inserted to the front of Range2.
    */
    template <typename Direction, typename Range1, typename Range2 = void>
        struct concatenate
    : operation::concatenate <
        typename range_tag <Range1>::type, typename range_tag <Range2>::type,
        Direction>::template apply <Range1, Range2> {};

    template <typename Range1, typename Range2>
        struct concatenate <Range1, Range2>
    : concatenate <typename default_direction <Range2>::type, Range1, Range2>
    {};

    namespace operation
    {
        /**
        Generic implementation: pushes Range1 to Range2 element-by-element.
        */
        template <typename Tag1, typename Tag2, typename Direction>
            struct concatenate
        {
            template <typename Range1, typename Range2,
                    bool Empty = meta::empty <Direction, Range1>::value>
                struct apply;

            template <typename Range1, typename Range2>
                struct apply <Range1, Range2, true>
            { typedef Range2 type; };

            template <typename Range1, typename Range2>
                struct apply <Range1, Range2, false>
            : meta::push <Direction,
                typename meta::first <Direction, Range1>::type,
                typename meta::concatenate <Direction,
                    typename meta::drop <Direction, Range1>::type, Range2>::type
            > {};
        };
    }

} // namespace meta

#endif  // META_CONCATENATE_HPP_INCLUDED

