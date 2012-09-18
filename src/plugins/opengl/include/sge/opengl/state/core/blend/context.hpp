/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_STATE_CORE_BLEND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_BLEND_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/core/blend/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace blend
{

class context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef sge::opengl::context::system::object &parameter;

	explicit
	context(
		parameter
	);

	~context();

	sge::opengl::state::core::blend::object const &
	default_state() const;

	static
	sge::opengl::context::system::id const
	static_id;
private:
	typedef fcppt::scoped_ptr<
		sge::opengl::state::core::blend::object
	> object_scoped_ptr;

	object_scoped_ptr const default_state_;
};

}
}
}
}
}

#endif
