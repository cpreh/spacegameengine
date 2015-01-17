/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/opengl/occlusion_query/context_fwd.hpp>
#include <sge/opengl/occlusion_query/holder.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class object
:
	public sge::renderer::occlusion_query::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::occlusion_query::context const &
	);

	~object()
	override;
private:
	void
	begin()
	override;

	void
	end()
	override;

	sge::renderer::occlusion_query::optional_pixel_count const
	result(
		sge::renderer::occlusion_query::blocking_wait block
	) const
	override;

	sge::opengl::occlusion_query::context const &context_;

	sge::opengl::occlusion_query::holder const holder_;
};

}
}
}

#endif
