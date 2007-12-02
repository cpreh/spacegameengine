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


#ifndef SGE_SYSTEMS_HPP_INCLUDED
#define SGE_SYSTEMS_HPP_INCLUDED

#include "plugin_manager.hpp"
#include "plugin.hpp"

#include "renderer/renderer.hpp"
#include "renderer/renderer_system.hpp"

#include "input/input_system.hpp"

#include "image/image_loader.hpp"

namespace sge {

struct systems {
	::sge::plugin_manager                         plugin_manager;

	::sge::plugin<sge::renderer_system>::ptr_type renderer_plugin;
	::sge::renderer_system_ptr                    renderer_system;
	::sge::renderer_parameters                    renderer_parameters;
	::sge::renderer_ptr                           renderer;

	::sge::plugin<sge::input_system>::ptr_type    input_plugin;
	::sge::input_system_ptr                       input_system;

	::sge::plugin<sge::image_loader>::ptr_type    image_loader_plugin;
	::sge::image_loader_ptr                       image_loader;

	systems() : renderer_parameters(display_mode(800,600,bit_depth::depth32)) {}

	template<typename T>
	bool init() { return T(*this); }
	template<typename T, typename P1>
	bool init(P1 p1) { return T(*this, p1); }
	template<typename T, typename P1, typename P2>
	bool init(P1 p1, P2 p2) { return T(*this, p1, p2); }
	template<typename T, typename P1, typename P2, typename P3>
	bool init(P1 p1, P2 p2, P3 p3) { return T(*this, p1, p2, p3); }
	template<typename T, typename P1, typename P2, typename P3, typename P4>
	bool init(P1 p1, P2 p2, P3 p3, P4 p4) { return T(*this, p1, p2, p3, p4); }
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	bool init(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) { return T(*this, p1, p2, p3, p4, p5); }
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	bool init(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) { return T(*this, p1, p2, p3, p4, p5, p6); }
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	bool init(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) { return T(*this, p1, p2, p3, p4, p5, p6, p7); }
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	bool init(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) { return T(*this, p1, p2, p3, p4, p5, p6, p7, p8); }
};

}

#endif
