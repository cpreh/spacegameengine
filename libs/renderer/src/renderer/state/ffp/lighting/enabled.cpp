//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::enabled::enabled(
	sge::renderer::state::ffp::lighting::ambient_color _ambient_color,
	sge::renderer::state::ffp::lighting::diffuse_from_vertex const _diffuse_from_vertex
)
:
	ambient_color_(
		std::move(
			_ambient_color
		)
	),
	diffuse_from_vertex_(
		_diffuse_from_vertex
	)
{
}

sge::renderer::state::ffp::lighting::ambient_color const &
sge::renderer::state::ffp::lighting::enabled::ambient_color() const
{
	return
		ambient_color_;
}

sge::renderer::state::ffp::lighting::diffuse_from_vertex
sge::renderer::state::ffp::lighting::enabled::diffuse_from_vertex() const
{
	return
		diffuse_from_vertex_;
}
