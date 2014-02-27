/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_STORE_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_STORE_IMPL_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/store.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/src/image/from_mizuiro_dim.hpp>
#include <sge/src/image/to_mizuiro_dim.hpp>
#include <mizuiro/image/dimension_impl.hpp>
#include <mizuiro/image/store_impl.hpp>


template<
	typename Format
>
sge::image::store<
	Format
>::store()
:
	internal_()
{}

template<
	typename Format
>
sge::image::store<
	Format
>::store(
	dim const &_size
)
:
	internal_(
		sge::image::to_mizuiro_dim<
			typename internal_type::dim
		>(
			_size
		)
	)
{
}

template<
	typename Format
>
sge::image::store<
	Format
>::store(
	store const &
) = default;

template<
	typename Format
>
sge::image::store<
	Format
> &
sge::image::store<
	Format
>::operator=(
	store const &
) = default;

template<
	typename Format
>
sge::image::store<
	Format
>::store(
	store &&
) = default;

template<
	typename Format
>
sge::image::store<
	Format
> &
sge::image::store<
	Format
>::operator=(
	store &&
) = default;

template<
	typename Format
>
sge::image::store<
	Format
>::~store()
{
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::pointer
sge::image::store<
	Format
>::data()
{
	return
		internal_.data();
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::const_pointer
sge::image::store<
	Format
>::data() const
{
	return
		internal_.data();
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::view_type const
sge::image::store<
	Format
>::view()
{
	return
		internal_.view();
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::const_view_type const
sge::image::store<
	Format
>::view() const
{
	return
		internal_.view();
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::wrapped_view_type const
sge::image::store<
	Format
>::wrapped_view()
{
	return
		sge::image::view::wrap(
			internal_.view()
		);
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::const_wrapped_view_type const
sge::image::store<
	Format
>::wrapped_view() const
{
	return
		sge::image::view::wrap(
			internal_.view()
		);
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::const_wrapped_view_type const
sge::image::store<
	Format
>::const_wrapped_view() const
{
	return
		this->wrapped_view();
}

template<
	typename Format
>
typename sge::image::store<
	Format
>::dim const
sge::image::store<
	Format
>::size() const
{
	return
		sge::image::from_mizuiro_dim<
			dim
		>(
			internal_.size()
		);
}

#endif
