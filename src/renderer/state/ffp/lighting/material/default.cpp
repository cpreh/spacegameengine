/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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


sge::renderer::state::ffp::lighting::material::parameters const
sge::renderer::state::ffp::lighting::material::default_()
{
	return
		sge::renderer::state::ffp::lighting::material::parameters(
			sge::renderer::state::ffp::lighting::diffuse_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .8)
						(sge::image::color::init::green() %= .8)
						(sge::image::color::init::blue() %= .8)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
			),
			sge::renderer::state::ffp::lighting::ambient_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .2)
						(sge::image::color::init::green() %= .2)
						(sge::image::color::init::blue() %= .2)
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
				0.0f
			)
		);
}
