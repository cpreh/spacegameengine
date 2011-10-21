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


#ifndef SGE_SHADER_VALUE_VARIANT_HPP_INCLUDED
#define SGE_SHADER_VALUE_VARIANT_HPP_INCLUDED

#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/renderer/glsl/int_type.hpp>
#include <sge/shader/matrix.hpp>
#include <fcppt/variant/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
typedef
fcppt::variant::object
<
	boost::mpl::vector7
	<
		renderer::vector2,
		renderer::vector3,
		renderer::vector4,
		renderer::scalar,
		renderer::glsl::int_type,
		shader::matrix,
		bool
	>
>
value_variant;
}
}

#endif
