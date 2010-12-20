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


#ifndef SGE_IMAGE_STORE_HPP_INCLUDED
#define SGE_IMAGE_STORE_HPP_INCLUDED

#include <sge/image/store_fwd.hpp>
#include <sge/image/dim.hpp>
#include <sge/symbol.hpp>
#include <mizuiro/image/store_decl.hpp>
#include <mizuiro/image/raw_view.hpp>
#include <mizuiro/access/raw.hpp>

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
		::mizuiro::access::raw
	> internal_type;
public:
	typedef typename internal_type::pointer pointer;

	typedef typename internal_type::const_pointer const_pointer;

	typedef typename image::dim<
		Format::dim_type::static_size
	>::type dim_type;

	typedef typename internal_type::view_type view_type;

	typedef typename internal_type::const_view_type const_view_type;

	SGE_SYMBOL store();

	SGE_SYMBOL explicit store(
		dim_type const &
	);

	SGE_SYMBOL store(
		store const &
	);

	SGE_SYMBOL store &
	operator=(
		store const &
	);

	SGE_SYMBOL ~store();

	SGE_SYMBOL pointer
	data();

	SGE_SYMBOL const_pointer
	data() const;

	SGE_SYMBOL view_type const
	view();

	SGE_SYMBOL const_view_type const
	view() const;

	SGE_SYMBOL dim_type const
	dim() const;
private:
	internal_type internal_;
};

}
}

#endif
