//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_DIRECTIONAL_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_DIRECTIONAL_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/light/direction.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace light
{

class directional
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	directional(
		sge::renderer::state::ffp::lighting::light::direction const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::direction const &
	direction() const;
private:
	sge::renderer::state::ffp::lighting::light::direction direction_;
};

}
}
}
}
}
}

#endif
