/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/detail/buffers.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/size_type.hpp>
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
	FCPPT_NONCOPYABLE(
		system_base
	);
public:
	sge::renderer::device &
	renderer() const;

	sge::renderer::vertex_declaration const &
	vertex_declaration() const;
protected:
	explicit system_base(
		sge::renderer::device &
	);

	~system_base();

	void
	allocate_buffers(
		sge::renderer::size_type needed_sprites
	);

	sge::renderer::vertex_buffer *
	vertex_buffer();

	sge::renderer::index_buffer *
	index_buffer();

	typedef typename detail::buffers<
		Choices
	>::type buffers_type;

	buffers_type const &
	buffers() const;
private:
	sge::renderer::device &renderer_;

	sge::renderer::vertex_declaration_ptr const vertex_declaration_;
	
	buffers_type buffers_;

	static sge::renderer::vf::dynamic::format const dyn_vertex_fmt_;
};

}
}

#endif
