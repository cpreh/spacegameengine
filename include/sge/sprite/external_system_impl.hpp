/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_EXTERNAL_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_EXTERNAL_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/system_base_impl.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/optional_size.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <fcppt/optional_impl.hpp>
#include <iterator>

template<
	typename Choices
>
sge::sprite::external_system<Choices>::external_system(
	renderer::device_ptr const rend
)
:
 	base(
		rend
	)
{}

template<
	typename Choices
>
template<
	typename Iterator,
	typename SortFunction,
	typename EqualFunction
>
void
sge::sprite::external_system<Choices>::render(
	Iterator const begin,
	Iterator const end,
	SortFunction const &sort_fun,
	EqualFunction const &equal_fun
)
{
	if(begin == end)
		return;
	
	sort_fun(
		begin,
		end
	);

	renderer::size_type const sprite_count(
		std::distance(
			begin,
			end
		)
	);

	base::allocate_buffers(
		sprite_count
	);

	renderer::vertex_buffer_ptr const vb(
		base::vertex_buffer()
	);

	renderer::index_buffer_ptr const ib(
		base::index_buffer()
	);

	detail::fill_geometry(
		begin,
		end,
		vb,
		ib,
		detail::optional_size(
			sprite_count
		)
	);

	base::matrices();

	renderer::device_ptr const rend(
		base::renderer()
	);

	renderer::state::scoped const state_(
		rend,
		render_states()
	);

	renderer::scoped_vertex_buffer const vb_context(
		rend,
		vb
	);

	detail::render(
		begin,
		end,
		equal_fun,
		rend,
		ib
	);
}

#endif
