//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_CORE_SAMPLER_FILTER_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_SAMPLER_FILTER_VISITOR_HPP_INCLUDED

#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class visitor
{
public:
	typedef sge::d3d9::state::core::sampler::state_vector result_type;

	result_type
	operator()(
		sge::renderer::state::core::sampler::filter::anisotropic::parameters const &
	) const;

	result_type
	operator()(
		sge::renderer::state::core::sampler::filter::normal::parameters const &
	) const;
};

}
}
}
}
}
}

#endif
