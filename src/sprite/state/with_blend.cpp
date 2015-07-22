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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <fcppt/from_optional.hpp>


sge::renderer::state::core::blend::object_unique_ptr
sge::sprite::state::with_blend::make(
	sge::renderer::device::core &_device,
	sge::sprite::state::with_blend::optional_extra_parameters const &_write_mask
)
{
	return
		_device.create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_variant{
					sge::renderer::state::core::blend::alpha_enabled{
						sge::renderer::state::core::blend::combined(
							sge::renderer::state::core::blend::source::src_alpha,
							sge::renderer::state::core::blend::dest::inv_src_alpha
						)
					}
				},
				fcppt::from_optional(
					_write_mask,
					[]{
						return
							sge::renderer::state::core::blend::write_mask_all();
					}
				)
			)
		);
}

void
sge::sprite::state::with_blend::set(
	sge::renderer::context::core &_context,
	sge::renderer::state::core::blend::object const &_state
)
{
	_context.blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref(
			_state
		)
	);
}

void
sge::sprite::state::with_blend::unset(
	sge::renderer::context::core &_context
)
{
	_context.blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref()
	);
}
