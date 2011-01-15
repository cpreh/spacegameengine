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


#include <IL/ilu.h>
#include "../file.hpp"
#include "../error.hpp"
#include "../format.hpp"
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/dim.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/log/global.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>

sge::devil::file::file(
	fcppt::filesystem::path const &_file
)
:
	impl_()
{
	bind_me();

	ilDisable(
		IL_FORMAT_SET
	);

	load(
		_file
	);

	if(
		format() == IL_COLOR_INDEX
	)
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("File \"")
				<< fcppt::filesystem::path_to_string(
					_file
				)
				<< FCPPT_TEXT("\" has a color palette, that sge won't handle.")
				<< FCPPT_TEXT(" Instead, the file will be reloaded and converted.")
				<< FCPPT_TEXT(" The process is inefficient and you should consider ")
				<< FCPPT_TEXT(" converting the file beforehand.")
		);

        	ilSetInteger(
			IL_FORMAT_MODE,
			IL_RGBA
		);

		ilEnable(
			IL_FORMAT_SET
		);

		load(
			_file
		);

		FCPPT_ASSERT(
			format() != IL_COLOR_INDEX
		);
	}
}

sge::devil::file::file(
	image2d::view::const_object const &_src
)
:
	impl_()
{
	data(
		_src
	);
}

sge::devil::file::~file()
{
}

sge::image2d::dim const
sge::devil::file::dim() const
{
	bind_me();

	return
		image2d::dim(
			static_cast<
				image2d::dim::value_type
			>(
				::ilGetInteger(
					IL_IMAGE_WIDTH
				)
			),
			static_cast<
				image2d::dim::value_type
			>(
				::ilGetInteger(
					IL_IMAGE_HEIGHT
				)
			)
		);
}

void
sge::devil::file::data(
	image2d::view::const_object const &_src
)
{
	bind_me();

	typedef fcppt::container::raw_vector<
		unsigned char
	> raw_vector_t;

	image2d::dim const src_dim(
		image2d::view::dim(
			_src
		)
	);

	image::color::format::type const fmt(
		image2d::view::format(
			_src
		)
	);

	raw_vector_t v(
		image::color::format_stride(fmt)
		* src_dim.content()
	);

	image::color::format::type const best_il_format(
		fmt
	);

	image2d::algorithm::copy_and_convert(
		_src,
		image2d::view::make(
			v.data(),
			src_dim,
			best_il_format,
			image2d::view::optional_pitch()
		)
	);

	image2d::dim const cur_dim(
		image2d::view::dim(
			_src
		)
	);

	ilTexImage(
		static_cast<
			ILuint
		>(
			cur_dim.w()
		),
		static_cast<
			ILuint
		>(
			cur_dim.h()
		),
		1,
		static_cast<
			ILubyte
		>(
			sge::image::color::element_count(
				best_il_format
			)
		),
		devil::to_il_format(
			best_il_format
		),
		devil::to_il_channel(
			best_il_format
		),
		const_cast<raw_vector_t::pointer>(v.data())
	);

	check_errors();
}

sge::image2d::view::const_object const
sge::devil::file::view() const
{
	bind_me();

	return
		image2d::view::make_const(
			const_cast<
				image::const_raw_pointer
			>(
				ilGetData()
			),
			dim(),
			devil::convert_format(
				ilGetInteger(
					IL_IMAGE_BITS_PER_PIXEL
				),
				format()
			),
			image2d::view::optional_pitch()
		);
}

void
sge::devil::file::save(
	fcppt::filesystem::path const &_file
)
{
	bind_me();

	ilEnable(IL_ORIGIN_SET);
	ilRegisterOrigin(IL_ORIGIN_UPPER_LEFT);

	ilSaveImage(
#ifdef UNICODE
		const_cast<
			wchar_t *
		>(
			fcppt::filesystem::path_to_string(
				_file
			).c_str()
		)
#else
		const_cast<
			char *
		>(
			fcppt::to_std_string(
				fcppt::filesystem::path_to_string(
					_file
				)
			).c_str()
		)
#endif
	);

	ilDisable(IL_ORIGIN_SET);

	check_errors();
}

void
sge::devil::file::bind_me() const
{
	ilBindImage(
		impl_.id()
	);

	check_errors();
}

void
sge::devil::file::load(
	fcppt::filesystem::path const &_file
)
{
	if(
		ilLoadImage(
#ifdef UNICODE
			const_cast<
				wchar_t *
			>(
				fcppt::filesystem::path_to_string(
					_file
				).c_str()
			)
#else
			const_cast<
				char *
			>(
				fcppt::to_std_string(
					fcppt::filesystem::path_to_string(
						_file
					)
				).c_str()
			)
#endif
		)
		== IL_FALSE
	)
		throw sge::image::exception(
			FCPPT_TEXT("ilLoadImage() failed! Could not load '")
			+ fcppt::filesystem::path_to_string(
				_file
			)
			+ FCPPT_TEXT("'!")
		);
}

ILenum
sge::devil::file::format() const
{
	return
		static_cast<
			ILenum
		>(
			::ilGetInteger(
				IL_IMAGE_FORMAT
			)
		);
}
