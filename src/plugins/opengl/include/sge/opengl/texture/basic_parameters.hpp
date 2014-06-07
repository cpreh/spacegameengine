/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class basic_parameters
{
	FCPPT_NONASSIGNABLE(
		basic_parameters
	);
public:
	basic_parameters(
		sge::opengl::context::system::object &,
		sge::opengl::context::device::object &
	);

	sge::opengl::context::system::object &
	system_context() const;

	sge::opengl::context::device::object &
	device_context() const;
private:
	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object &device_context_;
};

}
}
}

#endif
