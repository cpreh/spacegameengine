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


#ifndef SGE_SPRITE_DETAIL_UNSET_TEXTURE_STAGE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_UNSET_TEXTURE_STAGE_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

class unset_texture_stage
{
	FCPPT_NONASSIGNABLE(
		unset_texture_stage
	);
public:
	explicit unset_texture_stage(
		renderer::device &_device
	)
	:
		device_(_device)
	{
	}

	template<
		typename Level
	>
	void
	operator()(
		Level const &
	) const
	{
		device_.texture(
			renderer::texture::const_optional_base(),
			sge::renderer::stage(
				Level::value
			)
		);
	}
private:
	renderer::device &device_;
};

}
}
}

#endif
