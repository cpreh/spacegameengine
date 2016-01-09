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

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/vertex/buffer_fwd.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context()
	override;

	typedef
	fcppt::optional::reference<
		sge::opengl::vertex::buffer const
	>
	optional_buffer;

	void
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index,
		optional_buffer
	);

	optional_buffer
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index
	) const;

	typedef
	fcppt::optional::reference<
		sge::opengl::vertex::declaration const
	>
	optional_declaration;

	void
	vertex_declaration(
		optional_declaration
	);

	optional_declaration
	vertex_declaration() const;

	typedef void parameter;

	static sge::opengl::context::id const static_id;
private:
	typedef
	fcppt::container::index_map<
		optional_buffer
	>
	vertex_buffer_map;

	optional_declaration last_declaration_;

	mutable vertex_buffer_map last_buffers_;
};

}
}
}

#endif
