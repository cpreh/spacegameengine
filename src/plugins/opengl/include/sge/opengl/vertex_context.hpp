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


#ifndef SGE_OPENGL_VERTEX_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_CONTEXT_HPP_INCLUDED

#include <sge/opengl/vertex_buffer_fwd.hpp>
#include <sge/opengl/vertex_declaration_fwd.hpp>
#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace opengl
{

class vertex_context
:
	public sge::opengl::context::device::base
{
	FCPPT_NONCOPYABLE(
		vertex_context
	);
public:
	vertex_context();

	~vertex_context()
	override;

	sge::opengl::vertex_buffer const *
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index
	) const;

	void
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index,
		sge::opengl::vertex_buffer const *
	);

	void
	vertex_declaration(
		sge::opengl::vertex_declaration const *
	);

	sge::opengl::vertex_declaration const *
	vertex_declaration() const;

	typedef void parameter;

	static sge::opengl::context::device::id const static_id;
private:
	typedef fcppt::container::index_map<
		sge::opengl::vertex_buffer const *
	> vertex_buffer_map;

	sge::opengl::vertex_declaration const *last_declaration_;

	mutable vertex_buffer_map last_buffers_;
};

}
}

#endif
