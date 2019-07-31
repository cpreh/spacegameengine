//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_CONST_OBJECT_REF_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_CONST_OBJECT_REF_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/object_fwd.hpp>
#include <fcppt/reference.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace sampler
{

typedef fcppt::reference<
	sge::renderer::state::ffp::sampler::object const
> const_object_ref;

}
}
}
}
}

#endif
