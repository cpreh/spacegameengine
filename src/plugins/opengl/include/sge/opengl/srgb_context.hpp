/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_SRGB_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_SRGB_CONTEXT_HPP_INCLUDED

#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/srgb_context_fwd.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class srgb_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		srgb_context
	);
public:
	srgb_context();

	~srgb_context();

	sge::opengl::optional_enum const
	flag() const;

	typedef void parameter;

	static
	sge::opengl::context::system::id const
	static_id;
private:
	sge::opengl::optional_enum const flag_;
};

}
}

#endif
