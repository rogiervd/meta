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

#define BOOST_TEST_MODULE test_meta_scan
#include "../boost_unit_test.hpp"

#include "list.hpp"
#include "meta/scan.hpp"

typedef meta::list <> list0;
typedef meta::list <int, bool, float, double> list4;

typedef meta::weird_list <> weird_list0;
typedef meta::weird_list <int, bool, float, double> weird_list4;

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>

BOOST_AUTO_TEST_SUITE(test_meta_scan)

BOOST_AUTO_TEST_CASE (test_meta_scan) {
    using std::is_same;
    using boost::mpl::equal_to;
    namespace mpl = boost::mpl;

    typedef meta::scan <meta::push <mpl::_2, mpl::_1>,
        void, list0> list_void;
    typedef meta::scan <meta::push <mpl::_2, mpl::_1>,
        meta::list<>, list4> list_list;

    // These are actually private.
    /*
    BOOST_MPL_ASSERT ((
        std::is_same <list_list::direction, meta::list_direction>));
    BOOST_MPL_ASSERT ((
        std::is_same <list_list::function, meta::push <mpl::_2, mpl::_1>>));
    BOOST_MPL_ASSERT ((
        std::is_same <list_list::state, meta::list<>>));
    BOOST_MPL_ASSERT ((
        std::is_same <list_list::range, list4>));
    */

    // list_void.
    BOOST_MPL_ASSERT_NOT ((meta::empty <list_void>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <list_void>, boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((is_same <meta::first <list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <list_void>::type>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <list_void>::type>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <list_void>::type>, boost::mpl::size_t <0>>));

    // list_list.
    BOOST_MPL_ASSERT_NOT ((meta::empty <list_list>::type));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <list_list>, boost::mpl::size_t <5>>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <list_list>::type,
        meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <list_list>::type>::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, list_list>::type>::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, list_list>::type>::type,
        meta::list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, list_list>::type>::type,
        meta::list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, list_list>::type>));

    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <mpl::size_t <4>, list_list>::type>,
        boost::mpl::size_t <1>>));
    BOOST_MPL_ASSERT ((boost::mpl::equal_to <
        meta::size <meta::drop <mpl::size_t <5>, list_list>::type>,
        boost::mpl::size_t <0>>));

    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        void, list0> dir_list_void;
    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        meta::list<>, list4> dir_list_list;

    BOOST_MPL_ASSERT ((is_same <meta::first <dir_list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <dir_list_void>::type>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <dir_list_list>::type,
        meta::list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <dir_list_list>::type>::type,
        meta::list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, dir_list_list>::type>::type,
        meta::list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, dir_list_list>::type>::type,
        meta::list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, dir_list_list>::type>::type,
        meta::list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, dir_list_list>::type>));

    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        void, weird_list0> weird_list_void;
    typedef meta::scan <meta::list_direction,
        meta::push <meta::list_direction, mpl::_2, mpl::_1>,
        meta::weird_list<>, weird_list4> weird_list_list;

    BOOST_MPL_ASSERT ((is_same <meta::first <weird_list_void>::type, void>));
    BOOST_MPL_ASSERT ((meta::empty <meta::drop <weird_list_void>::type>));

    BOOST_MPL_ASSERT ((is_same <
        meta::first <weird_list_list>::type,
        meta::weird_list<> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <weird_list_list>::type>::type,
        meta::weird_list <int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <2>, weird_list_list>::type>::type,
        meta::weird_list <bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <3>, weird_list_list>::type>::type,
        meta::weird_list <float, bool, int> >));
    BOOST_MPL_ASSERT ((is_same <
        meta::first <meta::drop <mpl::size_t <4>, weird_list_list>::type>::type,
        meta::weird_list <double, float, bool, int> >));
    BOOST_MPL_ASSERT ((meta::empty <
        meta::drop <mpl::size_t <5>, weird_list_list>::type>));
}

BOOST_AUTO_TEST_SUITE_END()

