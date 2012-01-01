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


#include <sge/d3d9/texture/usage.hpp>
#include <sge/d3d9/texture/mipmap/auto_generate_usage.hpp>
#include <sge/d3d9/texture/mipmap/usage_visitor.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>


sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	renderer::texture::mipmap::all_levels_rep const &_all_levels
) const
{
	return
		mipmap::auto_generate_usage(
			_all_levels.auto_generate()
		);
}

sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	renderer::texture::mipmap::levels_rep const &_levels
) const
{
	return
		mipmap::auto_generate_usage(
			_levels.auto_generate()
		);
}

sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	renderer::texture::mipmap::off_rep const &
) const
{
	return
		d3d9::usage(
			0u
		);
}
