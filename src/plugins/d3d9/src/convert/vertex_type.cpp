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
#include <sge/d3d9/convert/vertex_type.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/element_type.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <sge/renderer/vf/dynamic/unspecified.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

struct visitor
{
	typedef D3DDECLTYPE result_type;

	result_type
	operator()(
		sge::renderer::vf::dynamic::pos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::normal const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::color const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::texpos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::unspecified const &
	) const;
};

D3DDECLTYPE
convert_vector(
	sge::renderer::vf::dynamic::vector const &
);

}

D3DDECLTYPE
sge::d3d9::convert::vertex_type(
	renderer::vf::dynamic::element const &_element
)
{
	return
		fcppt::variant::apply_unary(
			visitor(),
			_element.info()
		);
}

namespace
{

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::pos const &_pos
) const
{
	return
		::convert_vector(
			_pos.type()
		);
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::normal const &_normal
) const
{
	if(
		_normal.element_type()
		!= sge::renderer::vf::element_type::float_
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 only supports normals with a float element type!"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("")
		);

	return D3DDECLTYPE_FLOAT3;
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::color const &_color
) const
{
	if(
		sge::image::color::format_stride(
			_color.color_format()
		)
		!= 4u
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 can only use colors with a 4 bytes size!"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("")
		);

	return D3DDECLTYPE_D3DCOLOR;
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &_texpos
) const
{
	return
		::convert_vector(
			_texpos.type()
		);
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::unspecified const &
) const
{
	throw sge::renderer::unsupported(
		FCPPT_TEXT("Unspecified vertex formats are currently not supported in D3D9!"),
		FCPPT_TEXT(""),
		FCPPT_TEXT("")
	);
}

D3DDECLTYPE
convert_vector(
	sge::renderer::vf::dynamic::vector const &_vector
)
{
	if(
		_vector.element_type()
		!= sge::renderer::vf::element_type::float_
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 only supports float vectors for pos or texpos!"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("")
		);

	switch(
		_vector.elements()
	)
	{
	case 1:
		return D3DDECLTYPE_FLOAT1;
	case 2:
		return D3DDECLTYPE_FLOAT2;
	case 3:
		return D3DDECLTYPE_FLOAT3;
	case 4:
		return D3DDECLTYPE_FLOAT4;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("vf::pos or vf::texpos sizes of > 4 are not supported!")
	);
}

}
