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


#ifndef SGE_RENDERER_CREATE_INDEX_BUFFER_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_CREATE_INDEX_BUFFER_FROM_VIEW_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/index/dynamic/const_view_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Creates an index buffer copied from a view
 *
 * Creates an index buffer copied from \a view with resource flags \a flags.
 *
 * \param device The device to create the index buffer from
 * \param view The view to copy into the index buffer
 * \param flags The resource flags for the index buffer
 * \return A shared ptr to the created index buffer
 * \throw Anything that renderer::device::create_index_buffer throws
*/
SGE_RENDERER_SYMBOL
renderer::index_buffer_ptr const
create_index_buffer_from_view(
	renderer::device &device,
	index::dynamic::const_view const &view,
	renderer::resource_flags_field const &flags
);

}
}

#endif
