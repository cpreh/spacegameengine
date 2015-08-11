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


#include <sge/font/draw/create_ffp_sampler.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>


sge::renderer::state::ffp::sampler::optional_object_unique_ptr
sge::font::draw::create_ffp_sampler(
	sge::renderer::device::ffp &_device,
	sge::image::color::format const _color_format
)
{
	return
		_color_format
		==
		sge::image::color::format::a8
		?
			sge::renderer::state::ffp::sampler::optional_object_unique_ptr(
				_device.create_ffp_sampler_state(
					sge::renderer::state::ffp::sampler::parameters(
						sge::renderer::state::ffp::sampler::color_op(
							sge::renderer::state::ffp::sampler::op(
								sge::renderer::state::ffp::sampler::unary_op(
									sge::renderer::state::ffp::sampler::unary_op_type::arg,
									sge::renderer::state::ffp::sampler::arg1(
										sge::renderer::state::ffp::sampler::arg::vertex_color
									)
								)
							)
						),
						sge::renderer::state::ffp::sampler::alpha_op(
							sge::renderer::state::ffp::sampler::op(
								sge::renderer::state::ffp::sampler::unary_op(
									sge::renderer::state::ffp::sampler::unary_op_type::arg,
									sge::renderer::state::ffp::sampler::arg1(
										sge::renderer::state::ffp::sampler::arg::texture
									)
								)
							)
						)
					)
				)
			)
		:
			sge::renderer::state::ffp::sampler::optional_object_unique_ptr()
		;
}
