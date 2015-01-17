/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/volume_basic.hpp>
#include <sge/d3d9/volume/d3d_unique_ptr.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>
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

class volume
:
	public sge::d3d9::texture::volume_basic
{
	FCPPT_NONCOPYABLE(
		volume
	);
public:
	volume(
		IDirect3DDevice9 &,
		sge::renderer::texture::volume_parameters const &
	);

	~volume();
private:
	sge::renderer::texture::volume::dim const
	size() const;

	sge::renderer::texture::volume::color_buffer &
	level(
		sge::renderer::texture::mipmap::level
	);

	sge::renderer::texture::volume::color_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const;

	sge::d3d9::volume::d3d_unique_ptr
	get_level(
		sge::renderer::texture::mipmap::level
	);

	typedef
	std::vector<
		std::unique_ptr<
			sge::renderer::texture::volume::color_buffer
		>
	>
	level_vector;

	level_vector const levels_;
};

}
}
}

#endif
