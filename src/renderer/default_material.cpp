/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/init.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/default_material.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/emissive_color.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/shininess.hpp>


sge::renderer::material const
sge::renderer::default_material()
{
	return
		sge::renderer::material(
			sge::renderer::diffuse_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .8)
						(sge::image::color::init::green() %= .8)
						(sge::image::color::init::blue() %= .8)
						(sge::image::color::init::alpha() %= 1.)))),
			sge::renderer::ambient_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .2)
						(sge::image::color::init::green() %= .2)
						(sge::image::color::init::blue() %= .2)
						(sge::image::color::init::alpha() %= 1.)))),
			sge::renderer::specular_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .0)
						(sge::image::color::init::green() %= .0)
						(sge::image::color::init::blue() %= .0)
						(sge::image::color::init::alpha() %= 1.)))),
			sge::renderer::emissive_color(
				sge::image::color::any::object(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red() %= .0)
						(sge::image::color::init::green() %= .0)
						(sge::image::color::init::blue() %= .0)
						(sge::image::color::init::alpha() %= 1.)))),
			sge::renderer::shininess(
				0.0f));
}
