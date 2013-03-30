/*
Copyright 2011, 2012, 2013 Rogier van Dalen.

This file is part of Rogier van Dalen's Range library for C++.

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

/**
Fold operation that returns the results at each step.
*/

#ifndef META_SCAN_HPP_INCLUDED
#define META_SCAN_HPP_INCLUDED

#include "meta/fwd.hpp"
#include "meta/range.hpp"

namespace meta {

    template <typename Direction> struct scan_tag;
    template <typename Direction> struct empty_scan_tag;

    template <typename Direction, typename Function,
            typename State /*= void*/, typename Range /*= void*/>
        struct scan
    {
        typedef scan type;

    private:
        typedef Direction direction;
        typedef Function function;
        typedef State state;
        typedef Range range;

        // Operations need access to all typedefs because of default arguments.
        template <class Scan> friend struct range_tag;
        template <class Scan> friend struct default_direction;
        friend struct operation::size <scan_tag <Direction>, Direction>;
        friend struct operation::first <scan_tag <Direction>, Direction>;
        friend struct operation::drop_one <scan_tag <Direction>, Direction>;
    };

    /*
    Even if the underlying range of a scan is empty, scan<> itself has a first
    element: its State.
    empty_scan, on the other hand, is really empty.
    */
    template <typename Direction> struct empty_scan {
        typedef empty_scan type;
        typedef Direction direction;
    };

    // This should catch 2 and 3 parameters as long as Direction is not given.
    template <typename Function, typename State, typename Range>
        struct scan <Function, State, Range,
            typename boost::disable_if <is_direction <Function> >::type>
    : scan <typename default_direction <Range>::type,
        Function, State, Range> {};

    // Without State.
    template <typename Direction, typename Function, typename Range>
        struct scan <Direction, Function, Range,
            typename boost::enable_if <is_direction <Direction> >::type>
    : scan <Direction, Function,
        // First element of the list becomes the state.
        typename first <Direction, Range>::type,
        typename drop <Direction, Range>::type> {};

    template <typename Direction, typename Function,
            typename State, typename Range>
        struct range_tag <scan <Direction, Function, State, Range>>
    {
        // Direction may not be scan <...>::direction because of default
        // arguments.
        typedef scan_tag <
            typename scan <Direction, Function, State, Range>::direction> type;
    };

    template <typename Direction> struct range_tag <empty_scan <Direction> >
    { typedef empty_scan_tag <Direction> type; };

    template <typename Direction, typename Function,
            typename State, typename Range>
        struct default_direction <scan <Direction, Function, State, Range> >
    {
        typedef typename scan <Direction, Function, State, Range>::direction
            type;
    };

    template <typename Direction>
        struct default_direction <empty_scan <Direction> >
    { typedef Direction type; };

    namespace operation {

        // empty.
        template <typename Direction>
            struct empty <scan_tag <Direction>, Direction>
        { template <typename Range> struct apply : mpl::false_ {}; };

        template <typename Direction>
            struct empty <empty_scan_tag <Direction>, Direction>
        { template <typename Range> struct apply : mpl::true_ {}; };

        // size.
        template <typename Direction>
            struct size <scan_tag <Direction>, Direction>
        {
            template <typename Scan> struct apply
            : mpl::next <typename meta::size <Direction, typename Scan::range>
                >::type {};
        };

        template <typename Direction>
            struct size <empty_scan_tag <Direction>, Direction>
        { template <class Range> struct apply : mpl::size_t <0> {}; };

        // first: return State.
        template <typename Direction>
            struct first <scan_tag <Direction>, Direction>
        {
            // Specialising with scan <...> does not work, because of default
            // arguments.
            template <class Range> struct apply
            { typedef typename Range::state type; };
        };

        // drop_one
        template <typename Direction>
            struct drop_one <scan_tag <Direction>, Direction>
        {
            template <typename Scan, typename Enable = void> struct apply;

            // Underlying range is not empty.
            template <typename Scan>
                struct apply <Scan, typename boost::disable_if <
                    meta::empty <Direction, typename Scan::range>
                >::type>
            {
                // Apply Function to State and the first item of Range.
                typedef typename mpl::apply <typename Scan::function,
                        typename Scan::state,
                        typename meta::first <Direction, typename Scan::range
                            >::type
                    >::type new_state;

                typedef meta::scan <Direction,
                    typename Scan::function, new_state,
                    typename meta::drop <
                        Direction, typename Scan::range>::type> type;
            };

            // Underlying range is empty.
            template <typename Scan>
                struct apply <Scan, typename boost::enable_if <
                    meta::empty <Direction, typename Scan::range>
                >::type>
            { typedef empty_scan <Direction> type; };
        };

    } // namespace operation

} // namespace meta

#endif  // META_SCAN_HPP_INCLUDED

