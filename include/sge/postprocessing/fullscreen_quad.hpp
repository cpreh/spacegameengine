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


#ifndef SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED
#define SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace postprocessing
{
class fullscreen_quad
{
FCPPT_NONCOPYABLE(
	fullscreen_quad);
public:
	fullscreen_quad(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration &);

	void
	render(
		sge::renderer::context::core &);

	~fullscreen_quad();

	static
	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::device::core &);
private:
	sge::renderer::device::core &renderer_;
	sge::renderer::vertex::declaration &vertex_declaration_;
	sge::renderer::vertex::buffer_scoped_ptr const vertex_buffer_;
};
}
}

#endif
