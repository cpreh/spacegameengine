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


#ifndef SGE_SPRITE_BUFFERS_MULTI_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_MULTI_IMPL_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/allocate.hpp>
#include <sge/sprite/buffers/multi_decl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


template<
	typename Choices
>
sge::sprite::buffers::multi<
	Choices
>::multi(
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
	buffer_objects_(),
	slices_()
{
}

template<
	typename Choices
>
sge::sprite::buffers::multi<
	Choices
>::~multi()
{
}

template<
	typename Choices
>
typename sge::sprite::buffers::multi<
	Choices
>::slice_type &
sge::sprite::buffers::multi<
	Choices
>::allocate(
	sge::sprite::count const _num_sprites
)
{
	buffer_object new_object;

	sge::sprite::buffers::allocate<
		Choices
	>(
		parameters_,
		_num_sprites,
		new_object,
		sge::sprite::buffers::option_to_resource_flags(
			buffers_option_
		)
	);

	buffer_objects_.push_back(
		new_object
	);

	fcppt::container::ptr::push_back_unique_ptr(
		slices_,
		fcppt::make_unique_ptr<
			slice_type
		>(
			new_object,
			typename slice_type::offset_object() // initialize offsets to zero
		)
	);

	return
		slices_.back();
}

template<
	typename Choices
>
sge::sprite::buffers::parameters const &
sge::sprite::buffers::multi<
	Choices
>::parameters() const
{
	return parameters_;
}

#endif
