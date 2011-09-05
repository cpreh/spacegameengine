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


#ifndef SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS_HPP_INCLUDED

#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_ITERATE_FUNCTIONS(\
	req,\
	data,\
	elem\
)\
(\
	std::make_pair(\
		sge::plugin::library::symbol_string(\
			BOOST_PP_STRINGIZE(\
				elem\
			)\
		),\
		reinterpret_cast<\
			sge::plugin::library::function_base\
		>(\
			elem\
		)\
	)\
)

#endif
