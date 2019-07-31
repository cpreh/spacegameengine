//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/index.hpp>
#include <sge/d3d9/vf/convert/index_visitor.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_impl.hpp>


BYTE
sge::d3d9::vf::convert::index(
	sge::renderer::vf::dynamic::element const &_element,
	sge::d3d9::vf::texture_coordinate_count const _texture_coordinates
)
{
	return
		fcppt::variant::apply(
			sge::d3d9::vf::convert::index_visitor(
				_texture_coordinates
			),
			_element.info()
		);
}
