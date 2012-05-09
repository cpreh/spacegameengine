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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/vector_type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/text.hpp>


D3DDECLTYPE
sge::d3d9::vf::convert::vector_type(
	sge::renderer::vf::dynamic::vector const &_vector
)
{
	if(
		_vector.element_type()
		!=
		sge::renderer::vf::dynamic::element_type::float_
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 only supports float vectors for pos or texpos!"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("")
		);

	switch(
		_vector.element_count().get()
	)
	{
	case 1u:
		return D3DDECLTYPE_FLOAT1;
	case 2u:
		return D3DDECLTYPE_FLOAT2;
	case 3u:
		return D3DDECLTYPE_FLOAT3;
	case 4u:
		return D3DDECLTYPE_FLOAT4;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("vf::pos, vf::extra or vf::texpos sizes of > 4 are not supported!")
	);
}
