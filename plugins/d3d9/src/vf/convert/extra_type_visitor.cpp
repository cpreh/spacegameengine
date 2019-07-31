//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/vf/convert/color_type.hpp>
#include <sge/d3d9/vf/convert/extra_type_visitor.hpp>
#include <sge/d3d9/vf/convert/vector_type.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector_fwd.hpp>


sge::d3d9::vf::convert::extra_type_visitor::result_type
sge::d3d9::vf::convert::extra_type_visitor::operator()(
	sge::renderer::vf::dynamic::color const &_color
) const
{
	return
		sge::d3d9::vf::convert::color_type(
			_color
		);
}

sge::d3d9::vf::convert::extra_type_visitor::result_type
sge::d3d9::vf::convert::extra_type_visitor::operator()(
	sge::renderer::vf::dynamic::vector const &_vector
) const
{
	return
		sge::d3d9::vf::convert::vector_type(
			_vector
		);
}
