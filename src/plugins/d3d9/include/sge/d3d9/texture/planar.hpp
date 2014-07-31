/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/planar_basic.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

class planar
:
	public sge::d3d9::texture::planar_basic
{
	FCPPT_NONCOPYABLE(
		planar
	);
public:
	planar(
		IDirect3DDevice9 &,
		sge::renderer::texture::planar_parameters const &
	);

	~planar();
private:
	sge::renderer::texture::planar::dim const
	size() const;

	sge::renderer::texture::planar::color_buffer &
	level(
		sge::renderer::texture::mipmap::level
	);

	sge::renderer::texture::planar::color_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const;

	sge::d3d9::surface::d3d_unique_ptr
	get_level(
		sge::renderer::texture::mipmap::level
	);

	typedef
	std::vector<
		std::unique_ptr<
			sge::renderer::texture::planar::color_buffer
		>
	>
	level_vector;

	level_vector const levels_;
};

}
}
}

#endif
