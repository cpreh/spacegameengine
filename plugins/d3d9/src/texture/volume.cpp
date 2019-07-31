//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

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

FCPPT_PP_POP_WARNING

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
