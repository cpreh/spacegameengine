/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_MAKE_ONE_OP_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_MAKE_ONE_OP_HPP_INCLUDED

#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/renderer/state/ffp/sampler/pp_op_types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace sampler
{

template<
	typename OpType
>
sge::opengl::state::ffp::sampler::actor_vector
make_one_op(
	OpType const &
);

}
}
}
}
}

#define SGE_OPENGL_STATE_FFP_SAMPLER_DECLARE_MAKE_ONE_OP(\
	seq,\
	_,\
	op_type\
)\
extern \
template \
sge::opengl::state::ffp::sampler::actor_vector \
sge::opengl::state::ffp::sampler::make_one_op<\
	sge::renderer::state::ffp::sampler:: op_type\
>(\
	sge::renderer::state::ffp::sampler:: op_type const &\
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_STATE_FFP_SAMPLER_DECLARE_MAKE_ONE_OP,
	_,
	SGE_RENDERER_STATE_FFP_SAMPLER_PP_OP_TYPES
)

#endif
