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


#ifndef SGE_INIT_HPP_INCLUDED
#define SGE_INIT_HPP_INCLUDED

#include "systems.hpp"

namespace sge {
namespace init {

struct core {
	core(systems &) {
		// doint nothing for the moment
	}

	operator bool() const {
		return true;
	}
};

struct renderer {
	systems &sys;
	renderer(systems &sys, unsigned width, unsigned height) : sys(sys) {
		if (!sys.renderer_plugin)
			sys.renderer_plugin = sys.plugin_manager.get_plugin<sge::renderer_system>().load();;
		if (!sys.renderer_system)
			sys.renderer_system.reset(sys.renderer_plugin->get()());
		sys.renderer_parameters =
			sge::renderer_parameters(
				sge::display_mode(
					width,
					height,
					sge::bit_depth::depth32,
					0
				),
				true // windowed
			);
		sys.renderer = sys.renderer_system->create_renderer(sys.renderer_parameters);
	}

	operator bool() const {
		return sys.renderer;
	}
};

struct fullscreen_renderer {
	systems &sys;

	fullscreen_renderer(systems &sys, unsigned width, unsigned height, sge::bit_depth::type bdepth = sge::bit_depth::depth32, unsigned refresh_rate = 0, multi_sample_type multi=1, bool vsync=true) : sys(sys) {
		init(width, height, refresh_rate, bdepth, multi, vsync);
	}

	fullscreen_renderer(systems &sys, unsigned width, unsigned height, unsigned refresh_rate = 0, sge::bit_depth::type bdepth = sge::bit_depth::depth32, multi_sample_type multi=1, bool vsync=true) : sys(sys) {
		init(width, height, refresh_rate, bdepth, multi, vsync);
	}

	operator bool() const {
		return sys.renderer;
	}

private:
	void init(unsigned width, unsigned height, unsigned refresh_rate, sge::bit_depth::type bdepth, multi_sample_type multi, bool vsync) {
		if (!sys.renderer_plugin)
			sys.renderer_plugin = sys.plugin_manager.get_plugin<sge::renderer_system>().load();;
		if (!sys.renderer_system)
			sys.renderer_system.reset(sys.renderer_plugin->get()());
		sys.renderer_parameters =
			sge::renderer_parameters(
				sge::display_mode(
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
};

struct input {
	systems &sys;

	input(systems &sys) : sys(sys) {
		if (!sys.input_plugin)
			sys.input_plugin = sys.plugin_manager.get_plugin<sge::input_system>().load();
		sys.input_system.reset(sys.input_plugin->get()(sys.renderer->get_window()));
	}

	operator bool() const {
		return sys.input_system;
	}
};

struct image_loader {
	systems &sys;
	image_loader(systems &sys) : sys(sys) {
		if (!sys.image_loader_plugin)
			sys.image_loader_plugin = sys.plugin_manager.get_plugin<sge::image_loader>().load();
		sys.image_loader.reset(sys.image_loader_plugin->get()());
	}

	operator bool() const {
		return sys.image_loader;
	}
};

}
}

#endif
