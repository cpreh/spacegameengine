/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_SYSTEM_HPP_INCLUDED
#define SGE_D3D9_SYSTEM_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device_unique_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace d3d9
{

class system
:
	public renderer::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system();

	renderer::device_unique_ptr
	create_renderer(
		renderer::parameters const &,
		renderer::adapter,
		awl::window::object &
	);

	awl::visual::object_unique_ptr
	create_visual(
		awl::system::object &,
		sge::renderer::parameters const &
	);
private:
	typedef fcppt::scoped_ptr<
		IDirect3D9,
		fcppt::com_deleter
	> d3d_scoped_ptr;

	d3d_scoped_ptr const system_;
};

}
}

#endif
