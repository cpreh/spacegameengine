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


#ifndef SGE_OPENGL_STATE_FFP_CLIP_PLANE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_CLIP_PLANE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class context
:
	public sge::opengl::context::device::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef void parameter;

	context();

	~context();

	sge::renderer::state::index_count
	indices() const;

	void
	indices(
		sge::renderer::state::index_count
	);

	static
	sge::opengl::context::device::id const
	static_id;
private:
	sge::renderer::state::index_count indices_;
};

}
}
}
}
}

#endif
