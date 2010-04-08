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


#ifndef SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/index/dynamic/detail/variant_types.hpp>
#include <sge/renderer/index/dynamic/detail/make_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/symbol.hpp>
#include <fcppt/variant/object_decl.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{

template<
	bool IsConst
>
class basic_view
{
public:
	typedef fcppt::variant::object<
		typename boost::mpl::transform<
			typename detail::variant_types<
				IsConst
			>::type,
			detail::make_view<
				boost::mpl::_1
			>
		>::type
	> any_type;

	SGE_SYMBOL
	explicit basic_view(
		any_type const &
	);
	
	SGE_SYMBOL
	any_type const &
	any() const;

	SGE_SYMBOL
	renderer::size_type
	size() const;

	SGE_SYMBOL
	dynamic::format::type
	format() const;
private:
	any_type any_;	
};

}
}
}
}

#endif
