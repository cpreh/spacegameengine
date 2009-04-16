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


#include <sge/renderer/index/copy.hpp>
#include <sge/exception.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <sge/text.hpp>
#include <algorithm>

namespace
{

class copy_visitor : public boost::static_visitor<> {
public:
	template<
		typename T
	>
	void operator()(
		T const &src,
		T &dest) const
	{
		std::copy(
			src.begin(),
			src.end(),
			dest.begin());
	}

	template<
		typename T,
		typename U
	>
	void operator()(
		T,
		U) const
	{
		throw sge::exception(
			SGE_TEXT("Incompatible index::views in index::copy!"));
	}
};

}

void
sge::renderer::index::copy(
	const_view const &src,
	view const &dest)
{
	boost::apply_visitor(
		copy_visitor(),
		src,
		dest);
}
