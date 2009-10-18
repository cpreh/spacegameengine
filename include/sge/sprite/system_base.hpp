/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_SYSTEM_BASE_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_BASE_HPP_INCLUDED

#include <sge/sprite/matrix.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/math/matrix/basic_decl.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace sprite
{

class system_base {
	SGE_NONCOPYABLE(system_base)
public:
	SGE_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_SYMBOL void
	transform(
		matrix const &
	);
protected:
	explicit system_base(
		sge::renderer::device_ptr rend
	);
	
	SGE_SYMBOL void
	allocate_buffers(
		std::size_t needed_sprites
	);

	void matrices();

	SGE_SYMBOL sge::renderer::vertex_buffer_ptr const
	vertex_buffer() const;

	SGE_SYMBOL sge::renderer::index_buffer_ptr const
	index_buffer() const;
private:
	sge::renderer::device_ptr const  rend;

	matrix const
		transform_matrix,
		projection_matrix;
	
	matrix additional_transform_;

	sge::renderer::vertex_buffer_ptr vb;

	sge::renderer::index_buffer_ptr  ib;
};

}
}

#endif
