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


#ifndef SGE_RENDERER_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim3_fwd.hpp>
#include <sge/renderer/lock_box_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/color_buffer/volume_fwd.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL volume
:
	public sge::renderer::texture::base
{
	FCPPT_NONCOPYABLE(
		volume
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	volume();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~volume()
	override = 0;

	typedef sge::renderer::dim3 dim;

	typedef sge::renderer::lock_box rect;

	typedef sge::renderer::color_buffer::volume color_buffer;

	SGE_RENDERER_DETAIL_SYMBOL
	dim const
	size() const;

	virtual
	color_buffer &
	level(
		sge::renderer::texture::mipmap::level
	) = 0;

	virtual
	color_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const = 0;

	virtual
	sge::renderer::texture::mipmap::level_count const
	levels() const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	rect const
	area() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::texture::base::size_type
	content() const
	override;
};

}
}
}

#endif
