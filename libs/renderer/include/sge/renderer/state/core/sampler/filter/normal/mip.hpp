//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_MIP_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_MIP_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/filter/normal/mip_fwd.hpp>


namespace sge::renderer::state::core::sampler::filter::normal
{

enum class mip
{
	off,
	point,
	linear
};

}

#endif
