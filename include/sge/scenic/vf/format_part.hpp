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


#ifndef SGE_SCENIC_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SCENIC_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/scenic/vf/normal.hpp>
#include <sge/scenic/vf/position.hpp>
#include <sge/scenic/vf/texcoord.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace vf
{
typedef
sge::renderer::vf::part
<
	boost::mpl::vector3
	<
		sge::scenic::vf::position,
		sge::scenic::vf::normal,
		sge::scenic::vf::texcoord
	>
>
format_part;
}
}
}

#endif

