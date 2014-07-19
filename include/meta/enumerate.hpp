/*
Copyright 2011, 2012 Rogier van Dalen.

This file is part of Rogier van Dalen's Meta-programming library for C++.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

