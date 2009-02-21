/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

sge::renderer::texture_software::texture_software(
	dim_type const &new_dim,
	color_format::type const cf)
:
	dim_(),
	cf(cf),
	locked(false)
{
	resize(new_dim);
}

sge::renderer::texture_software::~texture_software()
{}

sge::renderer::dim_type const
sge::renderer::texture_software::dim() const
{
	return dim_;
}

sge::renderer::image_view const
sge::renderer::texture_software::lock(
	lock_rect const &lr,
	lock_flag_t const)
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked software texture"));
	locked = true;
	return subimage_view(
		make_image_view(
			raw_bytes.data(),
			dim(),
			cf),
		lr);
}

sge::renderer::const_image_view const
sge::renderer::texture_software::lock(
	lock_rect const &lr) const
{
	return subimage_view(make_image_view(&raw_bytes[0],dim(),cf),lr);
}

void sge::renderer::texture_software::unlock() const
{
	SGE_ASSERT_MESSAGE(
		locked,
		SGE_TEXT("software texture was not locked, though you tried to unlock"));

	locked = false;
}

sge::renderer::resource_flag_t
sge::renderer::texture_software::flags() const
{
	return resource_flags::dynamic;
}

// utility functions
sge::renderer::texture_software::internal_vector::size_type
sge::renderer::texture_software::byte_count() const
{
	return static_cast<
		internal_vector::size_type
	>(
		dim().w() * dim().h() * renderer::color_format_stride(cf));
}

void sge::renderer::texture_software::resize(dim_type const &new_dim)
{
	dim_ = new_dim;
	raw_bytes.resize(byte_count());
}


