//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/emissive_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/material/shininess.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::material::parameters::parameters(
	sge::renderer::state::ffp::lighting::diffuse_color _diffuse,
	sge::renderer::state::ffp::lighting::ambient_color _ambient,
	sge::renderer::state::ffp::lighting::specular_color _specular,
	sge::renderer::state::ffp::lighting::material::emissive_color _emissive,
	sge::renderer::state::ffp::lighting::material::shininess const _shininess
)
:
	diffuse_(
		std::move(
			_diffuse
		)
	),
	ambient_(
		std::move(
			_ambient
		)
	),
	specular_(
		std::move(
			_specular
		)
	),
	emissive_(
		std::move(
			_emissive
		)
	),
	shininess_(
		_shininess
	)
{
}

sge::renderer::state::ffp::lighting::diffuse_color const &
sge::renderer::state::ffp::lighting::material::parameters::diffuse() const
{
	return
		diffuse_;
}

sge::renderer::state::ffp::lighting::ambient_color const &
sge::renderer::state::ffp::lighting::material::parameters::ambient() const
{
	return
		ambient_;
}

sge::renderer::state::ffp::lighting::specular_color const &
sge::renderer::state::ffp::lighting::material::parameters::specular() const
{
	return
		specular_;
}

sge::renderer::state::ffp::lighting::material::emissive_color const &
sge::renderer::state::ffp::lighting::material::parameters::emissive() const
{
	return
		emissive_;
}

sge::renderer::state::ffp::lighting::material::shininess
sge::renderer::state::ffp::lighting::material::parameters::shininess() const
{
	return
		shininess_;
}
