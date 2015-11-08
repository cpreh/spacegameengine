/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either context 2
of the License, or (at your option) any later context.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/fun_ptr.hpp>
#include <sge/opengl/info/version.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace info
{

class context
{
public:
	sge::opengl::info::version
	version() const;

	sge::opengl::info::extension_set const &
	extensions() const;

	sge::opengl::info::fun_ptr
	load_function(
		std::string const &
	) const;
};

}
}
}

#endif
