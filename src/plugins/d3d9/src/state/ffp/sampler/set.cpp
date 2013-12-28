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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/logger.hpp>
#include <sge/d3d9/state/ffp/sampler/disable.hpp>
#include <sge/d3d9/state/ffp/sampler/object.hpp>
#include <sge/d3d9/state/ffp/sampler/set.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>


void
sge::d3d9::state::ffp::sampler::set(
	IDirect3DDevice9 &_device,
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &_states,
	sge::renderer::caps::texture_stages const _stages
)
{
	FCPPT_LOG_DEBUG(
		sge::d3d9::logger(),
		fcppt::log::_
			<<
			FCPPT_TEXT("Setting ")
			<<
			_states.size()
			<<
			FCPPT_TEXT(" ffp samplers.")
	);

	sge::renderer::texture::stage stage(
		0u
	);

	for(
		sge::renderer::state::ffp::sampler::const_object_ref_vector::const_iterator it(
			_states.begin()
		);
		it != _states.end();
		++it, ++stage
	)
		static_cast<
			sge::d3d9::state::ffp::sampler::object const &
		>(
			it->get()
		).set(
			stage
		);

	sge::d3d9::state::ffp::sampler::disable(
		_device,
		stage,
		_stages
	);
}
