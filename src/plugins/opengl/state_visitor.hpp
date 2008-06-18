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

#include <sge/renderer/states.hpp>
#include <boost/variant/static_visitor.hpp>

namespace sge
{
namespace ogl
{

class device;

class state_visitor : public boost::static_visitor<> {
public:
	state_visitor(device& rend);

	void operator()(renderer::int_state::type) const;
	void operator()(renderer::float_state::type) const;
	void operator()(renderer::bool_state::type) const;
	void operator()(renderer::color_state::type) const;
	void operator()(renderer::cull_mode::type) const;
	void operator()(renderer::depth_func::type) const;
	void operator()(renderer::stencil_func::type) const;
	void operator()(renderer::fog_mode::type) const;
	void operator()(renderer::draw_mode::type) const;
	void operator()(renderer::source_blend_func::type) const;
	void operator()(renderer::dest_blend_func::type) const;
private:
	device& rend;
};

}
}

#endif
