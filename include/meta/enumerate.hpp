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

#ifndef META_ENUMERATE_HPP_INCLUDED
#define META_ENUMERATE_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/scan.hpp"

namespace meta {

    template <typename Direction, typename Range =void> struct enumerate;

    template <typename Range> struct enumerate <Range>
    : enumerate <typename default_direction <Range>::type, Range> {};

    template <typename Direction, typename Range> struct enumerate {
        // Initialise with the before-the-begin element (-1, void).
        typedef mpl::pair <mpl::size_t <std::size_t (-1)>, void> before_begin;

        // Implementation without lambdas is faster.
        struct function {
            template <typename Previous, typename Type> struct apply
            {
                typedef typename mpl::next <typename Previous::first>::type
                    number;
                typedef mpl::pair <number, Type> type;
            };
        };

        // Enumerated list of types that starts with (-1, void).
        typedef scan <Direction, function, before_begin, Range> elements;
        // Remove the (-1, void)
        typedef typename drop <Direction, elements>::type type;
    };

} // namespace meta

#endif  // META_ENUMERATE_HPP_INCLUDED

