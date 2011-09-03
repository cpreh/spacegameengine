/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PLUGIN_LIBRARY_MAKE_INTERFACE_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE_HPP_INCLUDED

#include <sge/plugin/library/detail/interface_pre.hpp>
#include <sge/plugin/library/detail/interface_post.hpp>
#include <sge/plugin/library/detail/iterate_functions.hpp>
#include <sge/plugin/library/detail/version_function_name.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/function_map.hpp>
#include <sge/plugin/info.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(\
	plugin_info,\
	plugin_functions\
)\
namespace\
{\
\
sge::plugin::info const \
sge_info_function() \
{\
	return plugin_info;\
}\
\
}\
\
SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
	fcppt::assign::make_container<\
		sge::plugin::library::function_map::container\
	>(\
		std::make_pair(\
			sge::plugin::library::detail::version_function_name,\
			reinterpret_cast<\
				sge::plugin::library::function_base\
			>(\
				&sge_info_function\
			)\
		)\
	)\
	BOOST_PP_SEQ_FOR_EACH(\
		SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS,\
		void,\
		plugin_functions\
	) \
SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST

#endif
