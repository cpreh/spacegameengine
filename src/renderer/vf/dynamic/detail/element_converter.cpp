/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter.hpp>
#include <sge/src/renderer/vf/dynamic/detail/lock_interval.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::renderer::vf::dynamic::detail::element_converter::element_converter(
	sge::image::color::format::type const _original_color,
	sge::image::color::format::type const _backend_color,
	sge::renderer::vf::vertex_size const _stride,
	sge::renderer::vf::vertex_size const _offset
)
:
	original_color_(_original_color),
	backend_color_(_backend_color),
	stride_(_stride),
	offset_(_offset)
{
	FCPPT_ASSERT_PRE(
		sge::image::color::format_stride(
			original_color_
		)
		==
		sge::image::color::format_stride(
			backend_color_
		)
	);
}

sge::renderer::vf::dynamic::detail::element_converter::~element_converter()
{
}

void
sge::renderer::vf::dynamic::detail::element_converter::convert(
	detail::lock_interval const &_interval,
	sge::renderer::raw_pointer const _data,
	renderer::first_vertex const _pos,
	bool const _unlock
)
{
	if(
		original_color_ == backend_color_
	)
		return;

	// pos refers to the beginning of the lock
	FCPPT_ASSERT_PRE(
		_interval.lower()
		>= _pos.get()
	);

	sge::renderer::raw_pointer const begin(
		_data
		+ (_interval.lower() - _pos.get()) * stride_
		+ offset_
	);

	sge::image2d::dim const dim(
		1,
		_interval.upper() - _interval.lower()
	);

	sge::image2d::pitch const pitch(
		static_cast<
			sge::image2d::pitch::value_type
		>(
			stride_
			-
			sge::image::color::format_stride(
				original_color_
			)
		)
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			begin,
			dim,
			_unlock
			?
				original_color_
			:
				backend_color_
			,
			sge::image2d::view::optional_pitch(
				pitch
			)
		),
		sge::image2d::view::make(
			begin,
			dim,
			_unlock
			?
				backend_color_
			:
				original_color_
			,
			sge::image2d::view::optional_pitch(
				pitch
			)
		),
		sge::image::algorithm::may_overlap::yes
	);
}
