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


#ifndef SGE_RENDERER_VERTEX_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/linear_buffer_scoped_lock.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/buffer_types.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A scoped lock that locks a sge::renderer::vertex::buffer

\see sge::renderer::linear_buffer_scoped_lock
*/
typedef
sge::renderer::linear_buffer_scoped_lock<
	sge::renderer::vertex::buffer,
	sge::renderer::vertex::buffer_types
>
scoped_lock;

}
}
}

#endif
