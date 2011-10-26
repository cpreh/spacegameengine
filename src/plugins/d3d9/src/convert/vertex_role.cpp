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


#include <sge/d3d9/convert/vertex_role.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/unsupported.hpp>
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
	typedef D3DDECLUSAGE result_type;

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

}

D3DDECLUSAGE
sge::d3d9::convert::vertex_role(
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
	sge::renderer::vf::dynamic::pos const &
) const
{
	return D3DDECLUSAGE_POSITION;
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::normal const &
) const
{
	return D3DDECLUSAGE_NORMAL;
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::color const &
) const
{
	return D3DDECLUSAGE_COLOR;
}

visitor::result_type
visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &
) const
{
	return D3DDECLUSAGE_TEXCOORD;
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

}
