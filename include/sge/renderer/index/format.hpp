/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_INDEX_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_FORMAT_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Index,
	typename Constness
>
struct format
{
	typedef Index index_type;

	typedef Constness constness;

	typedef typename boost::mpl::if_<
		std::is_same<
			Constness,
			sge::renderer::index::const_tag
		>,
		sge::renderer::const_raw_pointer,
		sge::renderer::raw_pointer
	>::type pointer;
};

}
}
}

#endif
