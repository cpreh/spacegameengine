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


// FIXME: sadly, it seems that devil's unicode support is broken
#undef UNICODE
#undef _UNICODE

#include <IL/ilu.h>
#include "../object.hpp"
#include "../error.hpp"
#include "../conversion.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iconv.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/renderer/color.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/image_view_factory.hpp>

sge::devil::object::object(const path& file)
{
	bind_me();
	if(ilLoadImage(
//#ifdef UNICODE
//		const_cast<wchar_t*>(file.string().c_str())
//#else
		const_cast<char*>(iconv(file.string()).c_str())
//#endif
		) == IL_FALSE)
		throw exception(string(SGE_TEXT("ilLoadImage() failed! Could not load '")) += file.string() + SGE_TEXT("'!"));
}

sge::devil::object::object(
	const image::format::type type,
	const const_pointer format_data,
	const size_type size)
{
	if(!format_data || size == 0)
		throw exception(SGE_TEXT("load_image(): format_data or size is 0!"));
	bind_me();
	if(ilLoadL(convert_cast<ILenum>(type), const_cast<pointer>(format_data), static_cast<ILuint>(size)) == IL_FALSE)
		throw exception(SGE_TEXT("ilLoadL() failed!"));
}

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
	raw_vector<unsigned char> v(src.width() * src.height() * 4); // FIXME
	boost::gil::copy_and_convert_pixels(
		src,
		boost::gil::interleaved_view(
			src.width(),
			src.height(),
			reinterpret_cast<renderer::rgba8_color*>(v.data()),
			src.width() * 4));

	ilTexImage(
		static_cast<ILuint>(src.width()),
		static_cast<ILuint>(src.height()),
		1,
		4,
		IL_RGBA,
		IL_UNSIGNED_BYTE,
		const_cast<pointer>(v.data()));
	check_errors();
}

sge::renderer::const_image_view const
sge::devil::object::view() const
{
	bind_me();
	return renderer::const_image_view(
		boost::gil::interleaved_view(
			dim().w(),
			dim().h(),
			reinterpret_cast<renderer::rgba8_color const *>(
				ilGetData()),
			dim().w() * 4 // FIXME
			));
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

void sge::devil::object::save(path const &file)
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
