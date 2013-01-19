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


#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/default.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>


sge::renderer::state::ffp::sampler::parameters const
sge::renderer::state::ffp::sampler::default_()
{
	sge::renderer::state::ffp::sampler::op const op(
		sge::renderer::state::ffp::sampler::binary_op(
			sge::renderer::state::ffp::sampler::binary_op_type::modulate,
			sge::renderer::state::ffp::sampler::arg1(
				sge::renderer::state::ffp::sampler::arg::texture
			),
			sge::renderer::state::ffp::sampler::arg2(
				sge::renderer::state::ffp::sampler::arg::previous
			)
		)
	);

	return
		sge::renderer::state::ffp::sampler::parameters(
			sge::renderer::state::ffp::sampler::color_op(
				op
			),
			sge::renderer::state::ffp::sampler::alpha_op(
				op
			)
		);
}
