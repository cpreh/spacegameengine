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
#include "../file.hpp"
#include "../error.hpp"
#include "../format.hpp"
#include <sge/image/color/format_stride.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional_impl.hpp>

sge::devil::file::file(
	fcppt::filesystem::path const &file
)
{
	bind_me();
	if(ilLoadImage(
//#ifdef UNICODE
//		const_cast<wchar_t*>(file.string().c_str())
//#else
		const_cast<char*>(fcppt::to_std_string(file.string()).c_str())
//#endif
		) == IL_FALSE
	)
		throw exception(
			FCPPT_TEXT("ilLoadImage() failed! Could not load '")
			+ file.string()
			+ FCPPT_TEXT("'!"));
}

sge::devil::file::file(
	image::view::const_object const &src)
{
	data(src);
}

void sge::devil::file::bind_me() const
{
	ilBindImage(impl.id());
	check_errors();
}

sge::image::dim_type const
sge::devil::file::dim() const
{
	bind_me();
	return image::dim_type(
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT));
}

void sge::devil::file::data(
	image::view::const_object const &src)
{
	bind_me();

	typedef fcppt::container::raw_vector<
		unsigned char
	> raw_vector_t;

	image::dim_type const src_dim(
		image::view::dim(
			src
		)
	);

	image::color::format::type const fmt(
		image::view::format(
			src
		)
	);

	raw_vector_t v(
		image::color::format_stride(fmt)
		* src_dim.content()
	);

	image::color::format::type const best_il_format(
		fmt
	);

	image::algorithm::copy_and_convert(
		src,
		image::view::make(
			v.data(),
			src_dim,
			best_il_format,
			image::view::optional_pitch()
		)
	);

	image::dim_type const dim(
		image::view::dim(
			src
		)
	);

	ilTexImage(
		static_cast<ILuint>(dim.w()),
		static_cast<ILuint>(dim.h()),
		1,
		4, // always 4 channels
		to_il_format(
			best_il_format
		),
		to_il_channel(
			best_il_format
		),
		const_cast<raw_vector_t::pointer>(v.data())
	);

	check_errors();
}

sge::image::view::const_object const
sge::devil::file::view() const
{
	bind_me();
	return image::view::make(
		const_cast<
			image::const_raw_pointer
		>(
			ilGetData()
		),
		dim(),
		convert_format(
			ilGetInteger(IL_IMAGE_BITS_PER_PIXEL),
			ilGetInteger(IL_IMAGE_FORMAT)
		),
		image::view::optional_pitch()
	);
}

void
sge::devil::file::save(
	fcppt::filesystem::path const &file
)
{
	bind_me();

	ilEnable(IL_ORIGIN_SET);
	ilRegisterOrigin(IL_ORIGIN_UPPER_LEFT);

	ilSaveImage(
//#ifdef UNICODE
//		const_cast<wchar_t*>(file.string().c_str())
//#else
		const_cast<char*>(fcppt::to_std_string(file.string()).c_str())
//#endif
		);
	ilDisable(IL_ORIGIN_SET);
	check_errors();
}
