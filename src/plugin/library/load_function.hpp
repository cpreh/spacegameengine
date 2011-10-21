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


#ifndef SGE_PLUGIN_LIBRARY_LOAD_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_LOAD_FUNCTION_HPP_INCLUDED

#include "load_function_base.hpp"
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

template<
	typename Function
>
Function
load_function(
	library::object &_object,
	library::symbol_string const &_symbol
)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4191)
	return
		reinterpret_cast<
			Function
		>(
			library::load_function_base(
				_object,
				_symbol
			)
		);
FCPPT_PP_POP_WARNING
}

}
}
}

#endif
