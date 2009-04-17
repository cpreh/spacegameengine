/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/index/make_const_view.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

class visitor
: public boost::static_visitor<
	sge::renderer::index::const_view const
> {
public:
	template<
		typename T
	>
	sge::renderer::index::const_view const
	operator()(
		T const &) const;
};

}


sge::renderer::index::const_view const
sge::renderer::index::make_const_view(
	view const &v)
{
	return boost::apply_visitor(
		visitor(),
		v);
}

namespace
{

template<
	typename T
>
sge::renderer::index::const_view const
visitor::operator()(
	T const &v) const
{
	return sge::renderer::index::detail::basic_view<
		typename T::value_type const
	>(
		v.data(),
		v.size()
	);
}

}
