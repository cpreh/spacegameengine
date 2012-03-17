/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION_HPP_INCLUDED
#define ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION_HPP_INCLUDED

#include <alda/serialization/context_decl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


#define ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(\
	type_enum,\
	function_name\
) \
FCPPT_PP_PUSH_WARNING \
FCPPT_PP_DISABLE_VC_WARNING(4640) \
alda::serialization::context<\
	type_enum\
> &\
function_name()\
{\
	static alda::serialization::context<\
		type_enum\
	> object;\
\
	return object;\
} \
FCPPT_PP_POP_WARNING

#endif
