//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_VARIANT_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_VARIANT_FWD_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

using
variant
=
fcppt::variant::object<
	sge::renderer::state::core::sampler::filter::anisotropic::parameters,
	sge::renderer::state::core::sampler::filter::normal::parameters
>;

}
}
}
}
}
}

#endif
