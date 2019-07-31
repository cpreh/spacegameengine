//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LIBRARY_MAKE_INTERFACE_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE_HPP_INCLUDED

#include <sge/plugin/info.hpp>
#include <sge/plugin/library/function_map.hpp>
#include <sge/plugin/library/detail/interface_post.hpp>
#include <sge/plugin/library/detail/interface_pre.hpp>
#include <sge/plugin/library/detail/iterate_functions.hpp>
#include <sge/plugin/library/detail/make_version_function.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(\
	plugin_info,\
	plugin_functions\
)\
namespace\
{\
\
sge::plugin::info \
sge_info_function() \
{\
	return \
		plugin_info;\
}\
\
}\
\
FCPPT_PP_PUSH_WARNING \
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-variable-declarations) \
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors) \
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors) \
FCPPT_PP_DISABLE_CLANG_WARNING(-Wundefined-func-template) \
SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
	sge::plugin::library::function_map::container{\
		sge::plugin::library::detail::make_version_function(\
			&sge_info_function\
		) \
		BOOST_PP_SEQ_FOR_EACH(\
			SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS,\
			,\
			plugin_functions\
		)\
	}\
SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST \
FCPPT_PP_POP_WARNING

#endif
