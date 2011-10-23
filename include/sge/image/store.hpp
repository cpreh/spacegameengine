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


#ifndef SGE_IMAGE_STORE_HPP_INCLUDED
#define SGE_IMAGE_STORE_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/store_fwd.hpp>
#include <sge/image/detail/instantiate_symbol.hpp>
#include <sge/image/view/mizuiro_access.hpp>
#include <sge/image/view/wrapped_type.hpp>
#include <mizuiro/image/raw_view.hpp>
#include <mizuiro/image/store_decl.hpp>


namespace sge
{
namespace image
{

template<
	typename Format
>
class store
{
	typedef mizuiro::image::store<
		Format,
		sge::image::view::mizuiro_access
	> internal_type;
public:
	typedef typename internal_type::pointer pointer;

	typedef typename internal_type::const_pointer const_pointer;

	typedef typename image::dim<
		Format::dim::static_size
	>::type dim;

	typedef typename internal_type::view_type view_type;

	typedef typename internal_type::const_view_type const_view_type;

	typedef typename image::view::wrapped_type<
		view_type
	>::type wrapped_view_type;

	typedef typename image::view::wrapped_type<
		const_view_type
	>::type const_wrapped_view_type;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	store();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit store(
		dim const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	store(
		store const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	store &
	operator=(
		store const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~store();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	pointer
	data();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_pointer
	data() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	view_type const
	view();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_view_type const
	view() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	wrapped_view_type const
	wrapped_view();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_wrapped_view_type const
	wrapped_view() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	dim const
	size() const;
private:
	internal_type internal_;
};

}
}

#endif
