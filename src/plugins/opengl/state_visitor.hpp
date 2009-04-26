/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/state/states.hpp>
#include <boost/variant/static_visitor.hpp>

namespace sge
{
namespace ogl
{

class split_states;

class state_visitor : public boost::static_visitor<> {
public:
	explicit state_visitor(
		split_states &states);

	void operator()(renderer::state::int_::type) const;
	void operator()(renderer::state::uint_::type) const;
	void operator()(renderer::state::float_::type) const;
	void operator()(renderer::state::bool_::type) const;
	void operator()(renderer::state::color_::type) const;
	void operator()(renderer::state::cull_mode::type) const;
	void operator()(renderer::state::depth_func::type) const;
	void operator()(renderer::state::stencil_func::type) const;
	void operator()(renderer::state::alpha_func::type) const;
	void operator()(renderer::state::fog_mode::type) const;
	void operator()(renderer::state::draw_mode::type) const;
	void operator()(renderer::state::source_blend_func::type) const;
	void operator()(renderer::state::dest_blend_func::type) const;
private:
	split_states &states;
};

}
}

#endif
