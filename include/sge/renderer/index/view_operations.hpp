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


#ifndef SGE_RENDERER_INDEX_VIEW_OPERATIONS_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_OPERATIONS_HPP_INCLUDED

#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/export.hpp>
#include <boost/variant/static_visitor.hpp>

namespace sge
{
namespace renderer
{
namespace index
{

struct view_size
: boost::static_visitor<size_type> {

	template<
		typename T
	>
	SGE_SYMBOL size_type
	operator()(
		T const &) const;
};

struct view_stride
: boost::static_visitor<size_type> {

	template<
		typename T
	>
	SGE_SYMBOL size_type
	operator()(
		T const &) const;
};

struct view_format
: boost::static_visitor<format::type> {

	template<
		typename T
	>
	SGE_SYMBOL format::type
	operator()(
		T const &) const;
};

}
}
}

#endif
