/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_IMPL_STORE_BASIC_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_BASIC_IMPL_HPP_INCLUDED

#include <sge/image/basic_dim.hpp>
#include <sge/image/impl/from_mizuiro_dim.hpp>
#include <sge/image/impl/to_mizuiro_dim.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/store/basic.hpp>
#include <sge/image/view/wrap.hpp>
#include <mizuiro/no_init.hpp>
#include <mizuiro/image/dimension_impl.hpp>
#include <mizuiro/image/store_impl.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	internal_type &&_internal
)
:
	internal_(
		std::move(
			_internal
		)
	)
{
}

template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	dim const &_size,
	fcppt::no_init const &
)
:
	internal_(
		sge::image::impl::to_mizuiro_dim(
			_size
		),
		mizuiro::no_init{}
	)
{
}

template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	dim const &_size,
	mizuiro_color const &_init
)
:
	internal_{
		sge::image::impl::to_mizuiro_dim(
			_size
		),
		_init
	}
{
}

template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	dim const &_size,
	init_function const &_init
)
:
	basic(
		_size,
		fcppt::no_init{}
	)
{
	_init(
		this->view()
	);
}

template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	basic const &
) = default;

template<
	typename Format
>
sge::image::store::basic<
	Format
> &
sge::image::store::basic<
	Format
>::operator=(
	basic const &
) = default;

template<
	typename Format
>
sge::image::store::basic<
	Format
>::basic(
	basic &&
) = default;

template<
	typename Format
>
sge::image::store::basic<
	Format
> &
sge::image::store::basic<
	Format
>::operator=(
	basic &&
) = default;

template<
	typename Format
>
sge::image::store::basic<
	Format
>::~basic()
{
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::pointer
sge::image::store::basic<
	Format
>::data()
{
	return
		internal_.data();
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::const_pointer
sge::image::store::basic<
	Format
>::data() const
{
	return
		internal_.data();
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::view_type
sge::image::store::basic<
	Format
>::view()
{
	return
		internal_.view();
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::const_view_type
sge::image::store::basic<
	Format
>::view() const
{
	return
		internal_.view();
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::wrapped_view_type
sge::image::store::basic<
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
typename
sge::image::store::basic<
	Format
>::const_wrapped_view_type
sge::image::store::basic<
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
typename
sge::image::store::basic<
	Format
>::const_wrapped_view_type
sge::image::store::basic<
	Format
>::const_wrapped_view() const
{
	return
		this->wrapped_view();
}

template<
	typename Format
>
typename
sge::image::store::basic<
	Format
>::dim
sge::image::store::basic<
	Format
>::size() const
{
	return
		sge::image::impl::from_mizuiro_dim(
			internal_.size()
		);
}

#endif
