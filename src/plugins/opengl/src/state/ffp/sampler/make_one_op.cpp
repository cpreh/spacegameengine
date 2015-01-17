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


#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/opengl/state/ffp/sampler/instantiate_op_type.hpp>
#include <sge/opengl/state/ffp/sampler/make_one_op.hpp>
#include <sge/opengl/state/ffp/sampler/op_visitor.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename OpType
>
sge::opengl::state::ffp::sampler::actor_vector
sge::opengl::state::ffp::sampler::make_one_op(
	OpType const &_op
)
{
	return
		fcppt::variant::apply_unary(
			sge::opengl::state::ffp::sampler::op_visitor<
				OpType
			>(),
			_op.get().variant()
		);
}

#define SGE_OPENGL_STATE_FFP_SAMPLER_INSTANTIATE_MAKE_ONE_OP(\
	op_type\
)\
template \
sge::opengl::state::ffp::sampler::actor_vector \
sge::opengl::state::ffp::sampler::make_one_op<\
	op_type\
>(\
	op_type const &\
)

SGE_OPENGL_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE(
	SGE_OPENGL_STATE_FFP_SAMPLER_INSTANTIATE_MAKE_ONE_OP
);
