/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_VISUAL_HPP_INCLUDED
#define SGE_D3D9_VISUAL_HPP_INCLUDED

#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/visual/null_object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{

class visual
:
	public awl::backends::windows::visual::null_object,
	public sge::renderer::visual_base
{
	FCPPT_NONCOPYABLE(
		visual
	);
public:
	explicit
	visual(
		sge::renderer::pixel_format::object const &
	);

	~visual();
};

}
}

#endif
