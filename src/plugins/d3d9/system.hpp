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


#ifndef SGE_D3D9_SYSTEM_HPP_INCLUDED
#define SGE_D3D9_SYSTEM_HPP_INCLUDED

#include "d3dinclude.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/window/instance_fwd.hpp>
#include <sge/window/simple_parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

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

	renderer::device_ptr const
	create_renderer(
		renderer::parameters const &,
		renderer::adapter,
		sge::window::instance &
	);

	awl::window::instance_shared_ptr const
	create_window(
		awl::system::object &,
		sge::window::simple_parameters const &,
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
