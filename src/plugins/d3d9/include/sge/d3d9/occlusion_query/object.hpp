/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_D3D9_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/query/d3d_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace occlusion_query
{

class object
:
	public sge::renderer::occlusion_query::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		IDirect3DDevice9 &
	);

	~object();
private:
	void
	begin();

	void
	end();

	sge::renderer::occlusion_query::optional_pixel_count const
	result(
		sge::renderer::occlusion_query::blocking_wait
	) const;

	sge::d3d9::query::d3d_unique_ptr const query_;
};

}
}
}

#endif
