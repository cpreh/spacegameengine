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


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/algorithm/cac/choose.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/convert_visitor.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/function.hpp>
#include <sge/image/color/impl/dynamic/view/image_format.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/make_iterator_identity.hpp>
#include <mizuiro/image/algorithm/transform.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

// Unreachable code?
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4702)

template<
	typename Source,
	typename Dest
>
inline
void
convert(
	Source const &_source,
	Dest const &_dest,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	mizuiro::image::algorithm::transform(
		_source,
		_dest,
		sge::image::color::impl::dynamic::algorithm::cac::convert_visitor<
			sge::image::color::impl::dynamic::algorithm::cac::function<
				typename Source::format,
				typename Dest::format
			>
		>(
			sge::image::color::impl::dynamic::algorithm::cac::choose(
				sge::image::color::impl::dynamic::view::image_format(
					_source
				),
				sge::image::color::impl::dynamic::view::image_format(
					_dest
				)
			)
		),
		mizuiro::image::algorithm::make_iterator_identity{},
		sge::image::impl::algorithm::convert_uninitialized(
			_uninitialized
		)
	);
}

FCPPT_PP_POP_WARNING

}
}
}
}
}
}
}

#endif
