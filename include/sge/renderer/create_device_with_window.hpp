/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_CREATE_DEVICE_WITH_WINDOW_HPP_INCLUDED
#define SGE_RENDERER_CREATE_DEVICE_WITH_WINDOW_HPP_INCLUDED

#include <sge/renderer/adapter_type.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/renderer/window_parameters_fwd.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{

SGE_SYMBOL
sge::renderer::device_ptr const
create_device_with_window(
	sge::renderer::system_ptr,
	sge::renderer::parameters const &,
	sge::renderer::adapter_type,
	sge::renderer::window_parameters const &
);

}
}

#endif
