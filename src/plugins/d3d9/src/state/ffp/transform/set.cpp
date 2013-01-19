/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/state/ffp/transform/object.hpp>
#include <sge/d3d9/state/ffp/transform/set.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>


void
sge::d3d9::state::ffp::transform::set(
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &_state,
	sge::d3d9::state::ffp::transform::object const &_default
)
{
	(
		_state
		?
			static_cast<
				sge::d3d9::state::ffp::transform::object const &
			>(
				*_state
			)
		:
			_default
	).set(
		_mode
	);
}
