//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_CONVERT_LIGHT_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_LIGHT_VISITOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{
namespace light
{

class visitor
{
public:
	explicit
	visitor(
		D3DLIGHT9 &
	);

	typedef void result_type;

	result_type
	operator()(
		sge::renderer::state::ffp::lighting::light::directional const &
	) const;

	result_type
	operator()(
		sge::renderer::state::ffp::lighting::light::point const &
	) const;

	result_type
	operator()(
		sge::renderer::state::ffp::lighting::light::spot const &
	) const;
private:
	fcppt::reference<
		D3DLIGHT9
	> object_;
};

}
}
}
}
}

#endif
