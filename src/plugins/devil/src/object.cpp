/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



// FIXME: sadly, it seems that devil's unicode support is broken
#undef UNICODE
#undef _UNICODE

#include <IL/ilu.h>
#include "../object.hpp"
#include "../error.hpp"
#include "../format.hpp"
#include "../convert_image_format.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view_format.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/variant/object_impl.hpp>

sge::devil::object::object(
	filesystem::path const &file)
{
	bind_me();
	if(ilLoadImage(
//#ifdef UNICODE
//		const_cast<wchar_t*>(file.string().c_str())
//#else
		const_cast<char*>(iconv(file.string()).c_str())
//#endif
		) == IL_FALSE)
		throw exception(
			SGE_TEXT("ilLoadImage() failed! Could not load '")
			+ file.string()
			+ SGE_TEXT("'!"));
}

/*
sge::devil::object::object(
	image::format::type const type,
	const const_pointer format_data,
	const size_type size)
{
	if(!format_data || size == 0)
		throw exception(
			SGE_TEXT("load_image(): format_data or size is 0!"));
	bind_me();
	if(ilLoadL(
		convert_image_format(type),
		const_cast<pointer>(format_data),
		static_cast<ILuint>(size))
	== IL_FALSE)
		throw exception(
			SGE_TEXT("ilLoadL() failed!"));
}
*/

sge::devil::object::object(
	renderer::const_image_view const &src)
{
	data(src);
}

void sge::devil::object::bind_me() const
{
	ilBindImage(impl.id());
	check_errors();
}

const sge::image::object::dim_type sge::devil::object::dim() const
{
	bind_me();
	return dim_type(
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT));
}

void sge::devil::object::data(
	renderer::const_image_view const &src)
{
	bind_me();

	typedef container::raw_vector<
		unsigned char
	> raw_vector_t;

	renderer::dim_type const src_dim(
		renderer::image_view_dim(
			src));

	renderer::color_format::type const fmt(
		renderer::image_view_format(
			src));

	raw_vector_t v(
		renderer::color_format_stride(fmt)
		* src_dim.content());

	renderer::color_format::type const best_il_format(
		fmt);

	renderer::copy_and_convert_pixels(
		src,
		renderer::make_image_view(
			v.data(),
			src_dim,
			best_il_format));

	sge::renderer::dim_type const dim(
		sge::renderer::image_view_dim(
			src
		)
	);

	ilTexImage(
		static_cast<ILuint>(dim.w()),
		static_cast<ILuint>(dim.h()),
		1,
		4, // always 4 channels
		to_il_format(
			best_il_format),	
		to_il_channel(
			best_il_format),
		const_cast<raw_vector_t::pointer>(v.data()));
	check_errors();
}

sge::renderer::const_image_view const
sge::devil::object::view() const
{
	bind_me();
	return renderer::make_image_view(
		const_cast<unsigned char const *>(ilGetData()),
		dim(),
		convert_format(
			ilGetInteger(IL_IMAGE_BITS_PER_PIXEL),
			ilGetInteger(IL_IMAGE_FORMAT)));
}

void sge::devil::object::resample(
	dim_type const &dim_)
{
	if(dim() == dim_)
		return;
	bind_me();
	iluScale(static_cast<ILuint>(dim_.w()), static_cast<ILuint>(dim_.h()), 32);
	check_errors();
}

void sge::devil::object::save(
	filesystem::path const &file)
{
	bind_me();

	ilEnable(IL_ORIGIN_SET);
	ilRegisterOrigin(IL_ORIGIN_UPPER_LEFT);

	ilSaveImage(
//#ifdef UNICODE
//		const_cast<wchar_t*>(file.string().c_str())
//#else
		const_cast<char*>(iconv(file.string()).c_str())
//#endif
		);
	ilDisable(IL_ORIGIN_SET);
	check_errors();
}
