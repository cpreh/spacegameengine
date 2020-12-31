//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/light/variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::light::parameters::parameters(
	sge::renderer::state::ffp::lighting::diffuse_color _diffuse,
	sge::renderer::state::ffp::lighting::specular_color _specular,
	sge::renderer::state::ffp::lighting::ambient_color _ambient,
	sge::renderer::state::ffp::lighting::light::variant const _variant
)
:
	diffuse_(
		std::move(
			_diffuse
		)
	),
	specular_(
		std::move(
			_specular
		)
	),
	ambient_(
		std::move(
			_ambient
		)
	),
	variant_(
		_variant
	)
{
}

sge::renderer::state::ffp::lighting::diffuse_color const &
sge::renderer::state::ffp::lighting::light::parameters::diffuse() const
{
	return
		diffuse_;
}

sge::renderer::state::ffp::lighting::specular_color const &
sge::renderer::state::ffp::lighting::light::parameters::specular() const
{
	return
		specular_;
}

sge::renderer::state::ffp::lighting::ambient_color const &
sge::renderer::state::ffp::lighting::light::parameters::ambient() const
{
	return
		ambient_;
}

sge::renderer::state::ffp::lighting::light::variant const &
sge::renderer::state::ffp::lighting::light::parameters::variant() const
{
	return
		variant_;
}
