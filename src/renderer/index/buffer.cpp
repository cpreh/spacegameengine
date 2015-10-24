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


#include <sge/renderer/dim1.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/buffer/writable.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/src/renderer/buffer/instantiate_base.hpp>
#include <sge/src/renderer/buffer/instantiate_readable.hpp>
#include <sge/src/renderer/buffer/instantiate_writable.hpp>


sge::renderer::index::buffer::buffer()
:
	sge::renderer::buffer::writable<
		sge::renderer::index::tag
	>()
{
}

sge::renderer::index::buffer::~buffer()
{
}

sge::renderer::size_type
sge::renderer::index::buffer::linear_size() const
{
	return
		this->size().w();
}

SGE_RENDERER_BUFFER_INSTANTIATE_BASE(
	sge::renderer::index::tag
);

SGE_RENDERER_BUFFER_INSTANTIATE_READABLE(
	sge::renderer::index::tag
);

SGE_RENDERER_BUFFER_INSTANTIATE_WRITABLE(
	sge::renderer::index::tag
);
