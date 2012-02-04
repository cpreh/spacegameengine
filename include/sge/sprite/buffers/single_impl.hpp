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


#ifndef SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED

#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/buffers/allocate.hpp>
#include <sge/sprite/detail/buffers/vertex_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


template<
	typename Choices
>
sge::sprite::buffers::single<
	Choices
>::single(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::buffers::option::type const _buffers_option
)
:
	parameters_(
		_parameters
	),
	buffers_option_(
		_buffers_option
	),
	buffers_object_(),
	slice_()
{
}

template<
	typename Choices
>
sge::sprite::buffers::single<
	Choices
>::~single()
{
}

template<
	typename Choices
>
typename sge::sprite::buffers::single<
	Choices
>::slice_type &
sge::sprite::buffers::single<
	Choices
>::allocate(
	sge::sprite::count const _num_sprites
)
{
	sge::renderer::vertex_buffer *const vb(
		buffers_object_. template get<
			sge::sprite::buffers::roles::vertex_buffer
		>().get()
	);

	if(
		!vb
		||
		vb->size()
		<
		sge::sprite::detail::buffers::vertex_count<
			Choices
		>(
			_num_sprites
		)
	)
		sge::sprite::detail::buffers::allocate<
			Choices
		>(
			parameters_,
			_num_sprites,
			buffers_object_,
			sge::sprite::buffers::option_to_resource_flags(
				buffers_option_
			)
		);

	if(
		!slice_
	)
		slice_.take(
			fcppt::make_unique_ptr<
				slice_type
			>(
				buffers_object_,
				typename slice_type::offset_object() // initialize offsets to zero
			)
		);
	else
		slice_->reset(
			buffers_object_,
			typename slice_type::offset_object()
		);

	return
		*slice_;
}

template<
	typename Choices
>
sge::sprite::buffers::parameters const &
sge::sprite::buffers::single<
	Choices
>::parameters() const
{
	return parameters_;
}

#endif
