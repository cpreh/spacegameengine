#include <sge/renderer/default_material.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/material.hpp>

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
