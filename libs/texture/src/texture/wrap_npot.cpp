//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/texture/next_power_of_2.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/wrap_npot.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/math/dim/map.hpp>
#include <fcppt/math/vector/null.hpp>


sge::texture::part_unique_ptr
sge::texture::wrap_npot(
	sge::renderer::device::core &_device,
	sge::renderer::texture::planar_parameters const &_parameters
)
{
	// TODO: Use minimum required size here
	sge::renderer::dim2 const padded_size{
		fcppt::math::dim::map(
			_parameters.size(),
			[](
				sge::renderer::size_type const _sz
			)
			{
				return
					_sz
					==
					0u
					?
						1u
					:
						_sz
					;
			}
		)
	};

	return
		fcppt::unique_ptr_to_base<
			sge::texture::part
		>(
			fcppt::make_unique_ptr<
				sge::texture::part_raw_ptr
			>(
				_device.create_planar_texture(
					sge::renderer::texture::planar_parameters(
						_device.caps().non_power_of_2_textures().get()
						?
							padded_size
						:
							sge::texture::next_power_of_2(
								padded_size
							)
						,
						_parameters.format(),
						_parameters.mipmap(),
						_parameters.resource_flags(),
						_parameters.capabilities()
					)
				),
				sge::renderer::lock_rect(
					fcppt::math::vector::null<
						sge::renderer::lock_rect::vector
					>(),
					_parameters.size()
				)
			)
		);
}
