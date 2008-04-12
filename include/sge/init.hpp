/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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
#include "export.hpp"

namespace sge {
namespace init {

struct core {
	SGE_SYMBOL core(systems &);
	SGE_SYMBOL operator bool() const;
};

struct renderer {
	systems &sys;

	SGE_SYMBOL renderer(systems &sys, unsigned width, unsigned height);
	SGE_SYMBOL operator bool() const;
};

struct fullscreen_renderer {
	systems &sys;

	SGE_SYMBOL fullscreen_renderer(
		systems &sys,
		unsigned width,
		unsigned height,
		bit_depth::type bdepth
			= bit_depth::depth32,
		unsigned refresh_rate = 0,
		multi_sample_type multi = 1,
		bool vsync = true);

	SGE_SYMBOL fullscreen_renderer(
		systems &sys,
		unsigned width,
		unsigned height,
		unsigned refresh_rate = 0,
		bit_depth::type bdepth
			= bit_depth::depth32,
		multi_sample_type multi = 1,
		bool vsync = true);

	SGE_SYMBOL operator bool() const;
private:
	void init(
		unsigned width,
		unsigned height,
		unsigned refresh_rate,
		bit_depth::type bdepth,
		multi_sample_type multi,
		bool vsync);
};

struct input {
	systems &sys;

	SGE_SYMBOL input(systems &sys);
	SGE_SYMBOL operator bool() const;
};

struct image_loader {
	systems &sys;

	SGE_SYMBOL image_loader(systems &sys);
	SGE_SYMBOL operator bool() const;
};

}
}

#endif
