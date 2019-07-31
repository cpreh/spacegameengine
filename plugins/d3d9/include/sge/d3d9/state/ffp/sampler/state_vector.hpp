//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_SAMPLER_STATE_VECTOR_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_STATE_VECTOR_HPP_INCLUDED

#include <sge/d3d9/state/ffp/sampler/state.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace sampler
{

typedef std::vector<
	sge::d3d9::state::ffp::sampler::state
> state_vector;

}
}
}
}
}

#endif
