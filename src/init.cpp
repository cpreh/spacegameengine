/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (slashlife@slashlife.org)

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


#include <sge/init.hpp>

sge::init::core::core(systems &) {
	// do nothing for the moment
}

sge::init::core::operator bool() const {
	return true;
}

sge::init::renderer::renderer(systems &sys, ::sge::renderer::screen_size_t const &s)
: sys(sys)
{
	if (!sys.renderer_plugin)
		sys.renderer_plugin = sys.plugin_manager.get_plugin<sge::renderer::system>().load();
	if (!sys.renderer_system)
		sys.renderer_system.reset(sys.renderer_plugin->get()());
	sys.renderer_parameters =
		sge::renderer::parameters(
			sge::renderer::display_mode(
				s.w(),
				s.h(),
				sge::renderer::bit_depth::depth32,
				0
			),
			true // windowed
		);
	sys.renderer = sys.renderer_system->create_renderer(sys.renderer_parameters);
}

sge::init::renderer::operator bool() const {
	return sys.renderer;
}

sge::init::fullscreen_renderer::fullscreen_renderer(
	systems &sys,
	const unsigned width,
	const unsigned height,
	const sge::renderer::bit_depth::type bdepth,
	const unsigned refresh_rate,
	const sge::renderer::multi_sample_type multi,
	const bool vsync)
: sys(sys) {
	init(width, height, refresh_rate, bdepth, multi, vsync);
}

sge::init::fullscreen_renderer::fullscreen_renderer(
	systems &sys,
	const unsigned width,
	const unsigned height,
	const unsigned refresh_rate,
	const sge::renderer::bit_depth::type bdepth,
	const sge::renderer::multi_sample_type multi,
	const bool vsync)
: sys(sys) {
	init(width, height, refresh_rate, bdepth, multi, vsync);
}

sge::init::fullscreen_renderer::operator bool() const {
	return sys.renderer;
}

void sge::init::fullscreen_renderer::init(
	const unsigned width,
	const unsigned height,
	const unsigned refresh_rate,
	const sge::renderer::bit_depth::type bdepth,
	const sge::renderer::multi_sample_type multi,
	const bool vsync)
{
	if (!sys.renderer_plugin)
		sys.renderer_plugin = sys.plugin_manager.get_plugin<sge::renderer::system>().load();;
	if (!sys.renderer_system)
		sys.renderer_system.reset(sys.renderer_plugin->get()());
	sys.renderer_parameters =
		sge::renderer::parameters(
			sge::renderer::display_mode(
				width,
				height,
				bdepth,
				refresh_rate
			),
			false, // fullscreen
			multi,
			vsync
		);
	sys.renderer = sys.renderer_system->create_renderer(sys.renderer_parameters);
}

sge::init::input::input(systems &sys)
: sys(sys) {
	if (!sys.input_plugin)
		sys.input_plugin = sys.plugin_manager.get_plugin<sge::input::system>().load();
	sys.input_system.reset(sys.input_plugin->get()(sys.renderer->get_window()));
}

sge::init::input::operator bool() const {
	return sys.input_system;
}

sge::init::image_loader::image_loader(systems &sys)
: sys(sys) {
	if (!sys.image_loader_plugin)
		sys.image_loader_plugin = sys.plugin_manager.get_plugin<sge::image::loader>().load();
	sys.image_loader.reset(sys.image_loader_plugin->get()());
}

sge::init::image_loader::operator bool() const {
	return sys.image_loader;
}
