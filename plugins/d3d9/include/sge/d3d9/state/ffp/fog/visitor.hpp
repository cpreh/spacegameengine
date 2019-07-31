//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_FOG_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_FOG_VISITOR_HPP_INCLUDED

#include <sge/d3d9/state/render_vector.hpp>
#include <sge/renderer/state/ffp/fog/enabled_fwd.hpp>
#include <sge/renderer/state/ffp/fog/off_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace fog
{

class visitor
{
public:
	typedef sge::d3d9::state::render_vector result_type;

	result_type
	operator()(
		sge::renderer::state::ffp::fog::off const &
	) const;

	result_type
	operator()(
		sge::renderer::state::ffp::fog::enabled const &
	) const;
};

}
}
}
}
}

#endif
