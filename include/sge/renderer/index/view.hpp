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


#ifndef SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED

#include <sge/renderer/index/view_fwd.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/symbol.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
class view
{
public:
	BOOST_STATIC_ASSERT(
		is_format<
			Format
		>::value
	);

	typedef Format format_type;

	typedef typename format_type::type value_type;
	typedef value_type &reference;
	typedef value_type *pointer;
	typedef pointer iterator;

	typedef view<
		typename Format::const_type
	> const_type;

	typedef view<
		typename Format::nonconst_type
	> nonconst_type;

	typedef dynamic::basic_view<
		boost::is_const<
			value_type
		>::value
	> dynamic_view_type;		

	SGE_SYMBOL explicit view(
		pointer,
		size_type
	);

	SGE_SYMBOL view(
		nonconst_type const &
	);

	SGE_SYMBOL explicit view(
		dynamic_view_type const &
	);

	SGE_SYMBOL pointer
	data() const;

	SGE_SYMBOL size_type
	size() const;

	SGE_SYMBOL iterator
	begin() const;

	SGE_SYMBOL iterator
	end() const;

	SGE_SYMBOL index::dynamic::format::type
	format() const;
private:
	pointer data_;

	size_type size_;
};

}
}
}

#endif
