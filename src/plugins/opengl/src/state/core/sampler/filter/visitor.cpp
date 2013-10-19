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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropic.hpp>
#include <sge/opengl/state/core/sampler/filter/normal.hpp>
#include <sge/opengl/state/core/sampler/filter/visitor.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


sge::opengl::state::core::sampler::filter::visitor::visitor(
	sge::opengl::context::system::object &_system_context
)
:
	system_context_(
		_system_context
	)
{
}

sge::opengl::state::core::sampler::filter::visitor::result_type
sge::opengl::state::core::sampler::filter::visitor::operator()(
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_filter
) const
{
	return
		sge::opengl::state::core::sampler::filter::anisotropic(
			system_context_,
			_filter
		);
}

sge::opengl::state::core::sampler::filter::visitor::result_type
sge::opengl::state::core::sampler::filter::visitor::operator()(
	sge::renderer::state::core::sampler::filter::normal::parameters const &_filter
) const
{
	return
		sge::opengl::state::core::sampler::filter::normal(
			system_context_,
			_filter
		);
}
