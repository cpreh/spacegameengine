/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VF_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_VF_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_format.hpp>
#include <boost/function.hpp>
#include <vector>

namespace sge
{
namespace ogl
{
namespace vf
{

class format {
public:
	explicit vertex_format(
		renderer::vf::dynamic_format const &);
	renderer::vf::dynamic_format const &get() const;
	void use_me() const;
private:
	renderer::vf::dynamic_format const fmt;

	typedef boost::function<void ()> vertex_format_actor;
	typedef std::vector<vertex_format_actor> actor_array;
	actor_array actors;
};

}
}
}

#endif
