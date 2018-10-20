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


#ifndef SGE_IMAGE2D_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/image/view/declare_sub_out_of_range.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/traits/dimension.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image2d
{
namespace view
{

typedef
sge::image::view::sub_out_of_range<
	sge::image2d::tag
>
sub_out_of_range;

}
}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_IMAGE_VIEW_DECLARE_SUB_OUT_OF_RANGE(
	sge::image2d::tag
);

FCPPT_PP_POP_WARNING

#endif
