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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/basic_buffer.hpp>
#include <sge/d3d9/texture/basic_impl.hpp>
#include <sge/d3d9/texture/volume.hpp>
#include <sge/d3d9/texture/volume_basic.hpp>
#include <sge/d3d9/texture/volume_buffer.hpp>
#include <sge/d3d9/texture/volume_types.hpp>
#include <sge/d3d9/texturefuncs/get_volume_level.hpp>
#include <sge/d3d9/volume/d3d_unique_ptr.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/color_buffer/writable_volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::d3d9::texture::volume::volume(
	IDirect3DDevice9 &_device,
	sge::renderer::texture::volume_parameters const &_params
)
:
	sge::d3d9::texture::volume_basic(
		_device,
		_params
	),
	levels_(
		fcppt::algorithm::map<
			level_vector
		>(
			fcppt::make_int_range_count(
				sge::renderer::texture::mipmap::level(
					this->levels().get()
				)
			),
			[
				this
			](
				sge::renderer::texture::mipmap::level const _index
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::renderer::texture::volume::nonconst_buffer
					>(
						fcppt::make_unique_ptr<
							sge::d3d9::texture::volume_buffer
						>(
							sge::d3d9::texture::volume_buffer::d3d_buffer_create_function(
								std::bind(
									&sge::d3d9::texture::volume::get_level,
									this,
									_index
								)
							),
							this->color_format(),
							this->resource_flags()
						)
					);
			}
		)
	)
{
}

sge::d3d9::texture::volume::~volume()
{
}

sge::renderer::texture::volume::nonconst_buffer &
sge::d3d9::texture::volume::level(
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		*levels_[
			_level.get()
		];
}

sge::renderer::texture::volume::const_buffer const &
sge::d3d9::texture::volume::level(
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		*levels_[
			_level.get()
		];
}

sge::d3d9::volume::d3d_unique_ptr
sge::d3d9::texture::volume::get_level(
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		sge::d3d9::texturefuncs::get_volume_level(
			this->get(),
			_level
		);
}


template class
sge::d3d9::texture::basic<
	sge::d3d9::texture::volume_types
>;
