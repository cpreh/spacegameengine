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


#include <sge/renderer/texture_software.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>

sge::renderer::texture_software::texture_software(
	dim_type const &_new_dim,
	image::color::format::type const _cf
)
:
	dim_(),
	cf_(_cf),
	locked_(false)
{
	resize(
		_new_dim
	);
}

sge::renderer::texture_software::~texture_software()
{}

sge::renderer::dim2 const
sge::renderer::texture_software::dim() const
{
	return dim_;
}

sge::image2d::view::object const
sge::renderer::texture_software::lock(
	lock_rect const &_rect,
	lock_mode::type const
)
{
	FCPPT_ASSERT_MESSAGE(
		!locked_,
		FCPPT_TEXT("already locked software texture")
	);

	locked_ = true;

	return
		image2d::view::sub(
			image2d::view::make(
				raw_bytes_.data(),
				dim(),
				cf_,
				image2d::view::optional_pitch()
			),
			_rect
		);
}

sge::image2d::view::const_object const
sge::renderer::texture_software::lock(
	lock_rect const &_rect
) const
{
	return
		image2d::view::sub(
			image2d::view::make_const(
				raw_bytes_.data(),
				dim(),
				cf_,
				image2d::view::optional_pitch()
			),
			_rect
		);
}

void
sge::renderer::texture_software::unlock() const
{
	FCPPT_ASSERT_MESSAGE(
		locked_,
		FCPPT_TEXT("software texture was not locked, though you tried to unlock")
	);

	locked_ = false;
}

sge::renderer::resource_flags_field const
sge::renderer::texture_software::flags() const
{
	return resource_flags::dynamic;
}

// utility functions
sge::renderer::texture_software::internal_vector::size_type
sge::renderer::texture_software::byte_count() const
{
	return
		static_cast<
			internal_vector::size_type
		>(
			dim().w()
			* dim().h()
			* image::color::format_stride(
				cf_
			)
		);
}

void
sge::renderer::texture_software::resize(
	dim_type const &_dim
)
{
	dim_ = _dim;

	raw_bytes_.resize(
		byte_count()
	);
}
