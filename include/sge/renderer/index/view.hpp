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


#ifndef SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format_fwd.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/size_type.hpp>
#include <sge/renderer/index/to_nonconst_format.hpp>
#include <sge/renderer/index/view_fwd.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <fcppt/config/external_end.hpp>


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
		index::is_format<
			Format
		>::value
	);

	typedef Format format_type;

	typedef typename format_type::index_type value_type;

	typedef typename format_type::pointer pointer;

	typedef renderer::index::size_type size_type;

	typedef index::iterator<
		Format
	> iterator;

	typedef index::view<
		typename index::to_nonconst_format<
			Format
		>::type
	> nonconst_type;

	typedef dynamic::basic_view<
		boost::is_same<
			typename Format::constness,
			index::const_tag
		>::value
	> dynamic_view_type;

	SGE_RENDERER_SYMBOL
	explicit view(
		pointer,
		size_type
	);

	SGE_RENDERER_SYMBOL
	view(
		nonconst_type const &
	);

	SGE_RENDERER_SYMBOL
	explicit view(
		dynamic_view_type const &
	);

	SGE_RENDERER_SYMBOL
	pointer
	data() const;

	SGE_RENDERER_SYMBOL
	size_type
	size() const;

	SGE_RENDERER_SYMBOL
	iterator
	begin() const;

	SGE_RENDERER_SYMBOL
	iterator
	end() const;
private:
	pointer data_;

	size_type size_;
};

}
}
}

#endif
