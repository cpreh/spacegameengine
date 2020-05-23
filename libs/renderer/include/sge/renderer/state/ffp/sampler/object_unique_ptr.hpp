//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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

using
object_unique_ptr
=
fcppt::unique_ptr<
	sge::renderer::state::ffp::sampler::object
>;

}
}
}
}
}

#endif
