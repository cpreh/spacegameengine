//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color_value.hpp>
#include <sge/d3d9/state/convert/material.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>


D3DMATERIAL9 const
sge::d3d9::state::convert::material(
	sge::renderer::state::ffp::lighting::material::parameters const &_material
)
{
	D3DMATERIAL9 const ret =
	{
		sge::d3d9::convert::to_color_value(
			_material.diffuse().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.ambient().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.specular().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.emissive().get()
		),
		_material.shininess().get()
	};

	return ret;
}
