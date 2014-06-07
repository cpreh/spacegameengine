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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <fcppt/optional_impl.hpp>


sge::renderer::state::core::rasterizer::object_unique_ptr
sge::sprite::state::with_rasterizer::make(
	sge::renderer::device::core &_device,
	sge::sprite::state::with_rasterizer::optional_extra_parameters const &_enable_scissor_test
)
{
	return
		_device.create_rasterizer_state(
			sge::renderer::state::core::rasterizer::parameters(
				sge::renderer::state::core::rasterizer::cull_mode::off,
				sge::renderer::state::core::rasterizer::fill_mode::solid,
				_enable_scissor_test
				?
					*_enable_scissor_test
				:
					sge::renderer::state::core::rasterizer::enable_scissor_test(
						false
					)
			)
		);
}

void
sge::sprite::state::with_rasterizer::set(
	sge::renderer::context::core &_context,
	sge::sprite::state::with_rasterizer::state_type const &_state
)
{
	_context.rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref(
			_state
		)
	);
}

void
sge::sprite::state::with_rasterizer::unset(
	sge::renderer::context::core &_context
)
{
	_context.rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref()
	);
}
