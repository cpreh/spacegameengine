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


#ifndef SGE_SPRITE_BUFFERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_DECL_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/sprite/buffers_fwd.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/buffers/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class buffers
{
	FCPPT_NONCOPYABLE(
		buffers
	);
public:
	buffers(
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &,
		sge::sprite::buffers_option::type
	);

	~buffers();

	void
	allocate(
		sge::sprite::count
	);

	sge::renderer::vertex_buffer &
	vertex_buffer();

	sge::renderer::index_buffer &
	index_buffer();

	sge::renderer::vertex_buffer const &
	vertex_buffer() const;

	sge::renderer::index_buffer const &
	index_buffer() const;

	sge::renderer::device &
	renderer() const;

	sge::renderer::vertex_declaration const &
	vertex_declaration() const;
private:
	typedef typename sge::sprite::detail::buffers::object<
		Choices
	>::type internal_type;

	sge::renderer::device &renderer_;

	sge::renderer::vertex_declaration const &vertex_declaration_;

	sge::sprite::buffers_option::type const buffers_option_;

	internal_type buffers_;
};

}
}

#endif
