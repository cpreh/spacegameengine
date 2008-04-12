/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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


#ifndef SGE_OPENGL_STATE_VISITOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_VISITOR_HPP_INCLUDED

#include <sge/renderer/renderer_states.hpp>
#include <boost/variant/static_visitor.hpp>

namespace sge
{
namespace ogl
{

class renderer;

class state_visitor : public boost::static_visitor<> {
public:
	state_visitor(renderer& rend);

	void operator()(int_state::type) const;
	void operator()(float_state::type) const;
	void operator()(bool_state::type) const;
	void operator()(color_state::type) const;
	void operator()(cull_mode::type) const;
	void operator()(depth_func::type) const;
	void operator()(stencil_func::type) const;
	void operator()(fog_mode::type) const;
	void operator()(draw_mode::type) const;
	void operator()(source_blend_func::type) const;
	void operator()(dest_blend_func::type) const;
private:
	renderer& rend;
};

}
}

#endif
