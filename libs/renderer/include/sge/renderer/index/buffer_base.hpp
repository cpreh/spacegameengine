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


#ifndef SGE_RENDERER_INDEX_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_BASE_HPP_INCLUDED

#include <sge/renderer/buffer/detail/declare_base.hpp>
#include <sge/renderer/buffer/detail/declare_readable.hpp>
#include <sge/renderer/buffer/detail/declare_writable.hpp>
#include <sge/renderer/index/buffer_base_fwd.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/traits/color_tag.hpp>
#include <sge/renderer/index/traits/const_view_fwd.hpp>
#include <sge/renderer/index/traits/dimension.hpp>
#include <sge/renderer/index/traits/format_fwd.hpp>
#include <sge/renderer/index/traits/view_fwd.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_BUFFER_DETAIL_DECLARE_BASE(
	sge::renderer::index::tag
);

SGE_RENDERER_BUFFER_DETAIL_DECLARE_READABLE(
	sge::renderer::index::tag
);

SGE_RENDERER_BUFFER_DETAIL_DECLARE_WRITABLE(
	sge::renderer::index::tag
);

FCPPT_PP_POP_WARNING


#endif
