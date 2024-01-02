//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS_HPP_INCLUDED

#include <sge/plugin/loader_function.hpp> // IWYU pragma: keep
#include <sge/plugin/detail/from_loader_function.hpp> // IWYU pragma: keep
#include <sge/plugin/library/function_base_pair.hpp> // IWYU pragma: keep
#include <sge/plugin/library/symbol_string.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <fcppt/config/external_end.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS(req, data, elem) \
  , sge::plugin::library::function_base_pair( \
        sge::plugin::library::symbol_string(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, elem))), \
        sge::plugin::detail::from_loader_function<BOOST_PP_TUPLE_ELEM(0, elem)>( \
            sge::plugin::loader_function<BOOST_PP_TUPLE_ELEM(0, elem)>{ \
                BOOST_PP_TUPLE_ELEM(1, elem)}))

#endif
