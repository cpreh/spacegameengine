//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/extra_index.hpp>
#include <sge/d3d9/vf/convert/index_visitor.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>


sge::d3d9::vf::convert::index_visitor::index_visitor(
	sge::d3d9::vf::texture_coordinate_count const _texture_coordinates
)
:
	texture_coordinates_(
		_texture_coordinates
	)
{
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::pos const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::normal const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::color const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &_texpos
) const
{
	return
		static_cast<
			BYTE
		>(
			_texpos.index().get()
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::extra const &_extra
) const
{
	return
		static_cast<
			BYTE
		>(
			sge::d3d9::vf::convert::extra_index(
				texture_coordinates_,
				_extra.index()
			)
		);
}
