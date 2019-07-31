//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
