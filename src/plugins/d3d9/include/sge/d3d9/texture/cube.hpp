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


#ifndef SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/cube_basic.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

class cube
:
	public sge::d3d9::texture::cube_basic
{
	FCPPT_NONCOPYABLE(
		cube
	);
public:
	cube(
		IDirect3DDevice9 &,
		sge::renderer::texture::cube_parameters const &
	);

	~cube();
private:
	sge::renderer::texture::cube::size_type
	border_size() const;

	sge::renderer::texture::cube::color_buffer &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	);

	sge::renderer::texture::cube::color_buffer const &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) const;

	sge::d3d9::surface::d3d_unique_ptr
	get_level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	);

	typedef boost::ptr_vector<
		sge::renderer::texture::cube::color_buffer
	> level_map;

	typedef boost::ptr_vector<
		level_map
	> side_map;

	side_map sides_;
};

}
}
}

#endif
