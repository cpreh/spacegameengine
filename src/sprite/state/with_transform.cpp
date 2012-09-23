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


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/matrix.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/state/with_transform.hpp>
#include <fcppt/optional_impl.hpp>


sge::renderer::state::ffp::transform::object_unique_ptr
sge::sprite::state::with_transform::make(
	sge::renderer::device::ffp &_device,
	sge::sprite::state::with_transform::optional_extra_parameters const &_viewport
)
{
	if(
		!_viewport
	)
		return
			sge::renderer::state::ffp::transform::object_unique_ptr();

	sge::sprite::optional_matrix const matrix(
		sge::sprite::projection_matrix(
			*_viewport
		)
	);

	return
		matrix
		?
			_device.create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					*matrix
				)
			)
		:
			sge::renderer::state::ffp::transform::object_unique_ptr()
		;
}

void
sge::sprite::state::with_transform::set(
	sge::renderer::context::ffp &_context,
	sge::sprite::state::with_transform::state_type const &_state
)
{
	_context.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref(
			_state
		)
	);
}

void
sge::sprite::state::with_transform::unset(
	sge::renderer::context::ffp &_context
)
{
	_context.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref()
	);
}
