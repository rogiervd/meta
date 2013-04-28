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

/**
Define meta::vector, an MPL sequence.
Since it uses variadic template parameters, its type can remain a meta::vector<>
which makes it possible to pattern-match on it.
*/

#ifndef META_VECTOR_HPP_INCLUDED
#define META_VECTOR_HPP_INCLUDED

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/insert_range_fwd.hpp>

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>

#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/min_max.hpp>

#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/utility/enable_if.hpp>

#include "meta/fwd.hpp"
#include "meta/range.hpp"
#include "meta/fold_reverse.hpp"

namespace meta {

    namespace mpl = boost::mpl;

    // \todo Optimise operations
    struct vector_tag;

    template <typename ... Types> struct vector {
        typedef vector_tag tag;
        typedef vector type;
    };

    template <typename ... Types> struct range_tag <vector <Types ...> >
    { typedef vector_tag type; };

    namespace operation {

        template <> struct default_direction <vector_tag> {
            template <typename Range> struct apply
            { typedef meta::front type; };
        };

        // empty
        template <> struct empty <vector_tag, front> {
            template <typename Range, typename Void = void> struct apply;

            template <typename Void>
                struct apply <vector<>, Void> : mpl::true_ {};
            template <typename ... Types, typename Void>
                struct apply <vector <Types ...>, Void> : mpl::false_ {};
        };

        template <> struct empty <vector_tag, back>
        : empty <vector_tag, front> {};

        // size
        template <> struct size <vector_tag, front> {
            template <typename Range> struct apply;

            template <typename ... Types> struct apply <vector <Types ...>>
            : mpl::size_t <sizeof ... (Types)> {};
        };

        template <> struct size <vector_tag, back>
        : size <vector_tag, front> {};

        // first
        template <> struct first <vector_tag, front> {
            template <typename Vector> struct apply;
            template <typename FirstType, typename ... Types>
                struct apply <vector <FirstType, Types ...> >
            { typedef FirstType type; };
        };

        // first <back>.
        // This implementation should be O(1).
        // (The obvious implementation is recursive and O(n)).
        namespace first_back_detail {

            /**
            Wrapper to make sure the exact type does not get lost.
            */
            template <typename Type> struct wrap { typedef Type type; };

            /**
            Fake class that can be converted from anything.
            */
            template <typename Type> struct convert_from_any
            { template <class Any> convert_from_any (Any const &); };

            /**
            Return the last argument, where the number of arguments is the
            length of Types, plus 1.
            This allows the implementation of first <back> below.
            The last argument must be of type wrap <T>.
            */
            template <typename ... Types> struct return_last_type {
                template <typename LastType> wrap <LastType> operator() (
                    convert_from_any <Types> ..., wrap <LastType> const &);
            };

        } // namespace first_back_detail

        template <> struct first <vector_tag, back> {
            template <typename Vector> struct apply;
            template <typename ... Types> struct apply <vector <Types...> >
            {
                /**
                Pretend to call return_last_type with Types arguments + 1.
                By shifting up the arguments, by giving "0" as the first
                argument, the last argument becomes wrap <LastType> where
                LastType is the last type in the list.
                */
                typedef decltype (
                    std::declval <
                        first_back_detail::return_last_type <Types...>>() (
                        0, std::declval <first_back_detail::wrap <Types>>()...))
                    wrapped_last_type;
                typedef typename wrapped_last_type::type type;
            };
        };

        // drop
        template <> struct drop_one <vector_tag, front> {
            template <typename Vector> struct apply;

            template <typename FirstType, typename ... Types>
                struct apply <vector <FirstType, Types ...> >
            { typedef vector <Types ...> type; };
        };

        template <> struct drop_one <vector_tag, back> {
            template <typename Vector> struct apply;
            template <typename FirstType>
                struct apply <vector <FirstType> >
            {
                typedef vector<> type;
            };
            // Peel initial types off recursively
            template <typename FirstType, typename ... Types>
                struct apply <vector <FirstType, Types ...> >
            : meta::push <front, FirstType,
                typename apply <vector <Types ...> >::type> {};
        };

        // push
        template <> struct push <vector_tag, front> {
            template <typename NewElement, typename Vector> struct apply;

            template <typename NewElement, typename ... Types>
                struct apply <NewElement, vector <Types ...> >
            { typedef vector <NewElement, Types ...> type; };
        };
        template <> struct push <vector_tag, back> {
            template <typename NewElement, typename Vector> struct apply;

            template <typename NewElement, typename ... Types>
                struct apply <NewElement, vector <Types ...> >
            { typedef vector <Types ..., NewElement> type; };
        };

        /// Specialisation of transform uses C++11 intrinsics
        template <> struct transform <vector_tag, meta::front> {
            template <typename Function, typename Range> struct apply;

            template <typename Function, typename ... Types>
                struct apply <Function, vector <Types ...> >
            {
                typedef vector <typename mpl::apply <Function, Types>::type...
                    > type;
            };
        };
        template <> struct transform <vector_tag, meta::back>
        : transform <vector_tag, meta::front> {};

        /// Specialisation of concatenate
        template <> struct concatenate <vector_tag, vector_tag, meta::front> {
            template <typename Range1, typename Range2> struct apply;

            template <typename ... Types1, typename ... Types2>
                struct apply <vector <Types1 ...>, vector <Types2 ...> >
            {
                typedef vector <Types1 ..., Types2 ...> type;
            };
        };

        // Specialisation of fold
        // \todo Test
        template <> struct fold <vector_tag, meta::front> {
            template <typename Function, typename State, typename Range>
                struct apply;

            template <typename Function, typename State>
                struct apply <Function, State, vector<> >
            {
                typedef State type;
            };

            template <typename Function, typename State,
                typename Type1, typename ... OtherTypes>
            struct apply <Function, State, vector <Type1, OtherTypes ...> >
            : apply <Function,
                typename mpl::apply <Function, State, Type1>::type,
                vector <OtherTypes ...>
            > {};

            template <typename Function, typename State,
                typename Type1, typename Type2, typename ... OtherTypes>
            struct apply <Function, State,
                vector <Type1, Type2, OtherTypes ...> >
            : apply <Function,
                typename mpl::apply <Function,
                    typename mpl::apply <Function, State, Type1>::type,
                    Type2>::type,
                vector <OtherTypes ...>
            > {};

            template <typename Function, typename State,
                typename Type1, typename Type2, typename Type3,
                typename ... OtherTypes>
            struct apply <Function, State,
                vector <Type1, Type2, Type3, OtherTypes ...> >
            : apply <Function,
                typename mpl::apply <Function,
                    typename mpl::apply <Function,
                        typename mpl::apply <Function, State, Type1>::type,
                        Type2>::type,
                    Type3>::type,
                vector <OtherTypes ...>
            > {};
        };

    } // namespace operation


    // MPL-style iterator
    template <typename Position, typename Vector> struct vector_iterator {
        typedef boost::mpl::random_access_iterator_tag category;
        static const std::size_t index = Position::value;
    };

    template <typename Vector, typename Iterator>
        struct matching_iterator
    : mpl::false_ {};
    template <typename Vector, typename Position>
        struct matching_iterator <Vector, vector_iterator <Position, Vector> >
    : mpl::true_ {};

    /**
    Turn any range into a vector.
    This is often useful to exploit type pattern matching.
    */
    template <typename Direction, typename Sequence = void> struct as_vector
    : fold_reverse <Direction,
        push <front, mpl::_1, mpl::_2>, vector<>, Sequence> {};

    template <typename Sequence> struct as_vector <Sequence>
    : as_vector <typename default_direction <Sequence>::type, Sequence> {};

    template <typename ... Types> struct as_vector <front, vector <Types ...> >
    { typedef vector <Types ...> type; };

} // namespace meta

/*
MPL sequence compatibility

Forward sequence:
* empty<s>
* size<s>
* begin<s>
* end<s>
* front<s>

Bidirectional Sequence: + Forward Sequence
* begin<s> (Bidirectional Iterator)
* end<s> (Bidirectional Iterator)
* back<s>

Random Access Sequence: + Bidirectional
* begin <s> (Random Access Iterator)
* end <s> (Random Access Iterator)
* at <s, n>

Extensible Sequence:
* insert <s, pos, x>
- insert_range <s, pos, r>
* erase <s, pos, [last]>
* clear <s>

Front Extensible Sequence: +Extensible Sequence
* push_front <s, x>
* pop_front <s>
* front <s>

Back Extensible Sequence: +Extensible Sequence
* push_back <s, x>
* pop_back <s>
* back <s>

For the iterators:
* deref<i>
* next<i>
* prior<i>
* advance <i, n>
* distance <i, j>
*/

namespace boost { namespace mpl {

    template <typename ... Types>
        struct sequence_tag <meta::vector <Types ...> >
    { typedef meta::vector_tag type; };

    template <> struct empty_impl <meta::vector_tag>
    : meta::operation::empty <meta::vector_tag, meta::front> {};

    template <> struct size_impl <meta::vector_tag>
    : meta::operation::size <meta::vector_tag, meta::front> {};

    template <> struct front_impl <meta::vector_tag>
    : meta::operation::first <meta::vector_tag, meta::front> {};

    template <> struct push_front_impl <meta::vector_tag> {
        template <typename Vector, typename NewType> struct apply
        : meta::push <meta::front, NewType, Vector> {};
    };

    template <> struct pop_front_impl <meta::vector_tag>
    : meta::operation::drop_one <meta::vector_tag, meta::front> {};

    template <> struct clear_impl <meta::vector_tag> {
        template <typename Vector> struct apply
        { typedef meta::vector<> type; };
    };

    template <> struct back_impl <meta::vector_tag>
    : meta::operation::first <meta::vector_tag, meta::back> {};

    template <> struct push_back_impl <meta::vector_tag> {
        template <typename Vector, typename NewType> struct apply
        : meta::push <meta::back, NewType, Vector> {};
    };

    template <> struct pop_back_impl <meta::vector_tag>
    : meta::operation::drop_one <meta::vector_tag, meta::back> {};

    template <> struct at_impl <meta::vector_tag> {
        template <typename Vector, typename Position> struct apply
        : meta::first <meta::front,
            typename meta::drop <meta::front, Position, Vector>::type> {};
    };

    template <> struct erase_impl <meta::vector_tag> {
        template <typename Vector, std::size_t first, typename Last = na>
            struct apply_one_c;
        template <typename Vector, std::size_t first, std::size_t last>
            struct apply_range_c;
        template <typename Vector, typename First, typename Last>
            struct apply_range;

        // Main
        template <typename Vector, typename First, typename Last>
            struct apply
        {
            // Check that the first iterator matches.
            typedef meta::matching_iterator <Vector, First> matches;
            static_assert (matches::value, "Iterator must match sequence");
            typedef typename boost::enable_if <matches,
                apply_one_c <Vector, First::index, Last> >::type::type type;
        };

        // Erase range: check Last and forward to apply_range_c.
        template <typename Vector, std::size_t first, typename Last>
            struct apply_one_c
        {
            // Check that the last iterator matched
            typedef meta::matching_iterator <Vector, Last> matches;
            static_assert (matches::value, "Iterator must match sequence");
            typedef typename boost::enable_if <matches,
                apply_range_c <Vector, first, Last::index> >::type::type type;
        };

        // Erase one element
        template <typename FirstType, typename ... Types>
            struct apply_one_c <meta::vector <FirstType, Types ...>, 0>
        { typedef meta::vector <Types ...> type; };

        template <typename FirstType, typename ... Types, std::size_t first>
            struct apply_one_c <meta::vector <FirstType, Types ...>, first>
        : meta::push <meta::front, FirstType,
            typename apply_one_c <meta::vector <Types ...>, first - 1>::type
        > {};

        // Erase a range
        template <typename ... Types>
            struct apply_range_c <meta::vector <Types ...>, 0, 0>
        {  typedef meta::vector <Types ...> type; };
        // (resolve specialisation)
        template <typename FirstType, typename ... Types>
            struct apply_range_c <meta::vector <FirstType, Types ...>, 0, 0>
        { typedef meta::vector <FirstType, Types ...> type; };

        template <typename FirstType, typename ... Types, std::size_t last>
            struct apply_range_c <meta::vector <FirstType, Types ...>, 0, last>
        : apply_range_c <meta::vector <Types ...>, 0, last - 1> {};

        template <typename FirstType, typename ... Types,
            std::size_t first, std::size_t last>
        struct apply_range_c <meta::vector <FirstType, Types ...>, first, last>
        : meta::push <meta::front, FirstType,
            typename apply_range_c <meta::vector <Types ...>,
                first - 1, last  - 1>::type> {};
    };

    template <> struct insert_impl <meta::vector_tag> {
        template <typename Vector, std::size_t index, typename NewType>
            struct apply_c;

        template <typename Vector, typename Position, typename NewType>
            struct apply
        {
            typedef meta::matching_iterator <Vector, Position> matches;
            static_assert (matches::value, "Iterator must match sequence");
            typedef typename boost::enable_if <matches,
                apply_c <Vector, Position::index, NewType> >::type::type type;
        };

        template <typename ... Types, typename NewType>
        struct apply_c <meta::vector <Types ...>, 0, NewType>
        : meta::push <meta::front, NewType, meta::vector <Types ...> > {};
        // Resolve specialisations
        template <typename FirstType, typename ... Types, typename NewType>
        struct apply_c <meta::vector <FirstType, Types ...>, 0, NewType>
        : meta::push <meta::front, NewType,
            meta::vector <FirstType, Types ...> > {};

        template <typename FirstType, typename ... Types,
            std::size_t index, typename NewType>
        struct apply_c <meta::vector <FirstType, Types ...>, index, NewType>
        : meta::push <meta::front, FirstType,
            typename apply_c <meta::vector <Types ...>, index - 1, NewType
                >::type
        > {};
    };

    template <> struct insert_range_impl <meta::vector_tag> {
        template <typename Vector, std::size_t index, typename newTypes>
            struct apply_c;

        template <typename Vector, typename Position, typename NewTypes>
            struct apply
        {
            typedef meta::matching_iterator <Vector, Position> matches;
            static_assert (matches::value, "Iterator must match sequence");
            typedef typename boost::enable_if <matches,
                apply_c <Vector, Position::index, NewTypes> >::type::type type;
        };

        template <typename Vector, typename NewTypes, typename Enable = void>
            struct push_front_range;

        template <typename Vector, typename NewTypes>
            struct push_front_range <Vector, NewTypes,
                typename boost::enable_if <empty <NewTypes> >::type>
        { typedef Vector type; };

        template <typename Vector, typename NewTypes>
            struct push_front_range <Vector, NewTypes,
                typename boost::disable_if <empty <NewTypes> >::type>
        : meta::push <meta::front, typename mpl::front <NewTypes>::type,
            typename push_front_range <Vector,
                typename meta::drop <meta::front, NewTypes>::type>::type > {};

        template <typename ... Types, typename NewTypes>
        struct apply_c <meta::vector <Types ...>, 0, NewTypes>
        : push_front_range <meta::vector <Types ...>, NewTypes> {};
        // Resolve specialisations
        template <typename FirstType, typename ... Types, typename NewTypes>
        struct apply_c <meta::vector <FirstType, Types ...>, 0, NewTypes>
        : push_front_range <meta::vector <FirstType, Types ...>, NewTypes> {};

        template <typename FirstType, typename ... Types,
            std::size_t index, typename NewTypes>
        struct apply_c <meta::vector <FirstType, Types ...>, index, NewTypes>
        : meta::push <meta::front, FirstType,
            typename apply_c <meta::vector <Types ...>, index - 1, NewTypes
                >::type
        > {};
    };

    /**** vector_iterator ****/

    template <> struct begin_impl <meta::vector_tag> {
        template <typename Vector> struct apply
        { typedef meta::vector_iterator <mpl::size_t <0>, Vector> type; };
    };

    template <> struct end_impl <meta::vector_tag> {
        template <typename Vector> struct apply {
            typedef meta::vector_iterator <
                typename boost::mpl::size <Vector>::type, Vector> type;
        };
    };

    template <typename  Position, typename Vector>
        struct deref <meta::vector_iterator <Position, Vector> >
    : boost::mpl::at <Vector, Position> {};

    template <typename Position, typename Vector>
        struct next <meta::vector_iterator <Position, Vector> >
    {
        typedef typename next <Position>::type new_position;
        static_assert (less_equal <new_position, size <Vector> >::value,
            "Attempt to increment iterator beyond the end of the sequence.");
        typedef meta::vector_iterator <new_position
                , Vector
            > type;
    };

    template <typename Position, typename ... Types>
        struct prior <
            meta::vector_iterator <Position, meta::vector <Types ...> > >
    {
        typedef typename prior <Position>::type new_position;
        static_assert (greater_equal <new_position, mpl::size_t <0> >::value,
            "Attempt to decrement iterator before the start of the sequence.");
        typedef meta::vector_iterator <
                new_position, meta::vector <Types ...>
            > type;
    };

    template <typename Position, typename Vector, typename Distance>
        struct advance <
            meta::vector_iterator <Position, Vector>,
            Distance
        >
    {
        typedef typename plus <Position, Distance>::type new_position;
        static_assert (less_equal <new_position, size <Vector> >::value,
            "Attempt to increment iterator beyond the end of the sequence.");
        static_assert (greater_equal <new_position, mpl::size_t <0> >::value,
            "Attempt to decrement iterator before the start of the sequence.");

        typedef meta::vector_iterator <new_position, Vector> type;
    };

    template <typename Position1, typename Position2, typename Vector>
        struct distance <
            meta::vector_iterator <Position1, Vector>,
            meta::vector_iterator <Position2, Vector>
        >
    : minus <Position2, Position1> {};

}} // namespace boost::mpl

#endif  // META_VECTOR_HPP_INCLUDED

