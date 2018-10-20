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


#ifndef SGE_IMAGE_DS_INVALID_COPY_HPP_INCLUDED
#define SGE_IMAGE_DS_INVALID_COPY_HPP_INCLUDED

#include <sge/image/declare_invalid_copy.hpp>
#include <sge/image/invalid_copy.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/ds/traits/format_fwd.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image
{
namespace ds
{

typedef
sge::image::invalid_copy<
	sge::image::ds::tag
>
invalid_copy;

}
}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_IMAGE_DECLARE_INVALID_COPY(
	sge::image::ds::tag
);

FCPPT_PP_POP_WARNING

#endif
