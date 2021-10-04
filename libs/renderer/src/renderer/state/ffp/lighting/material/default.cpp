//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/default.hpp>
#include <sge/renderer/state/ffp/lighting/material/emissive_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/material/shininess.hpp>


sge::renderer::state::ffp::lighting::material::parameters
sge::renderer::state::ffp::lighting::material::default_()
{
	return
		{
			sge::renderer::state::ffp::lighting::diffuse_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::green() %= .8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::blue() %= .8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
			),
			sge::renderer::state::ffp::lighting::ambient_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .2) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::green() %= .2) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::blue() %= .2) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
			),
			sge::renderer::state::ffp::lighting::specular_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .0)
						(sge::image::color::init::green() %= .0)
						(sge::image::color::init::blue() %= .0)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
			),
			sge::renderer::state::ffp::lighting::material::emissive_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .0)
						(sge::image::color::init::green() %= .0)
						(sge::image::color::init::blue() %= .0)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
			),
			sge::renderer::state::ffp::lighting::material::shininess(
				0.0F
			)
		};
}
