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


#include <sge/renderer/dim1.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/impl/buffer/instantiate_base.hpp>
#include <sge/renderer/impl/buffer/instantiate_readable.hpp>
#include <sge/renderer/impl/buffer/instantiate_writable.hpp>
#include <sge/renderer/index/buffer_base.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/view.hpp>


SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_BASE(
	sge::renderer::index::tag
);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_READABLE(
	sge::renderer::index::tag
);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_WRITABLE(
	sge::renderer::index::tag
);
