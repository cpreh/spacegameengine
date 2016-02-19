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


#ifndef SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief A buffer for storing indices

An index buffer can hold a fixed amount of indices in a given index format, of
which there are currently two of:

<ul>
<li>16 bit indices</li>
<li>32 bit indices</li>
</ul>

After an index buffer has been created, its size cannot be changed. To store
data in it, it has to be locked first, which will return a view for accessing
the data. Unlocking the buffer will make the update actually take place.

\see sge::renderer::device::create_index_buffer
\see sge::renderer::device::render_indexed
\see sge::renderer::index::const_scoped_lock
\see sge::renderer::index::scoped_lock
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer
:
	public
		sge::renderer::index::buffer_base
{
	FCPPT_NONCOPYABLE(
		buffer
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	buffer();
public:
	/**
	\brief Returns the resource flags the buffer has been created with
	*/
	virtual
	sge::renderer::resource_flags_field
	resource_flags() const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::size_type
	linear_size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~buffer()
	override;
};

}
}
}

#endif
