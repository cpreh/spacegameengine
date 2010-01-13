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


#ifndef SGE_SPRITE_SYSTEM_BASE_DECL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_BASE_DECL_HPP_INCLUDED

#include <sge/sprite/system_base_fwd.hpp>
#include <sge/sprite/matrix.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/matrix/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class system_base
{
	FCPPT_NONCOPYABLE(system_base)
public:
	typedef typename sprite::matrix<
		typename Choices::type_choices::float_type
	>::type matrix;

	sge::renderer::device_ptr const
	renderer() const;

	void
	transform(
		matrix const &
	);

	void
	matrices();
protected:
	explicit system_base(
		sge::renderer::device_ptr rend
	);

	~system_base();

	void
	allocate_buffers(
		sge::renderer::size_type needed_sprites
	);

	sge::renderer::vertex_buffer_ptr const
	vertex_buffer() const;

	sge::renderer::index_buffer_ptr const
	index_buffer() const;
private:
	sge::renderer::device_ptr const rend;

	matrix const
		transform_matrix,
		projection_matrix;

	matrix additional_transform_;

	sge::renderer::vertex_buffer_ptr vb;

	sge::renderer::index_buffer_ptr  ib;

	static sge::renderer::vf::dynamic_format const dyn_vertex_fmt;
};

}
}

#endif
