/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/capabilities_field.hpp>
#include <sge/image/file_exception.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/system.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension const supported_extension(
	FCPPT_TEXT("png")
);

sge::media::extension_set const const_extensions((
	fcppt::assign::make_container<
		sge::media::extension_set
	>
	(
		supported_extension
	)
));

}

sge::libpng::system::system()
{
}

sge::libpng::system::~system()
{
}

sge::image2d::file_ptr const
sge::libpng::system::load(
	fcppt::filesystem::path const &_path
)
{
	fcppt::io::cifstream file_stream(
		_path,
		std::ios_base::binary);

	if(
		!file_stream.is_open()
	)
		throw image::file_exception(
			sge::image::optional_path(
				_path
			),
			FCPPT_TEXT("couldn't open file"));
	try
	{
		return
			fcppt::make_shared_ptr<
				libpng::file
			>(
				fcppt::ref(
					file_stream),
				sge::image::optional_path(
					_path)
			);
	}
	catch(
		sge::image::unsupported_format const &
	)
	{
		return sge::image2d::file_ptr();
	}
}

sge::image2d::file_ptr const
sge::libpng::system::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	if(
		_extension &&
		_extension
		!=
		sge::media::optional_extension(
			supported_extension
		)
	)
		return sge::image2d::file_ptr();

	typedef
	boost::iostreams::stream<
		boost::iostreams::array_source
	>
	stream_type;

	stream_type raw_stream(
		reinterpret_cast<
			boost::iostreams::array_source::char_type const *
		>(
			_range.begin()
		),
		reinterpret_cast<
			boost::iostreams::array_source::char_type const *
		>(
			_range.end()
		)
	);

	try
	{
		return
			fcppt::make_shared_ptr<
				libpng::file
			>(
				fcppt::ref(
					raw_stream),
				sge::image::optional_path()
			);
	}
	catch (
		sge::image::unsupported_format const &)
	{
		return sge::image2d::file_ptr();
	}
}

sge::image2d::file_ptr const
sge::libpng::system::create(
	image2d::view::const_object const &_view,
	sge::media::optional_extension const &_extension
)
{
	return
		(
			_extension
			&&
			*_extension != supported_extension
		)
		?
			sge::image2d::file_ptr()
		:
			fcppt::make_shared_ptr<
				file
			>(
				fcppt::cref(
					_view
				)
			)
		;
}

void
sge::libpng::system::save(
	image2d::file const &_file,
	fcppt::filesystem::path const &_path
)
{
	dynamic_cast<
		libpng::file const &
	>(
		_file
	).save(
		_path
	);
}

sge::image::capabilities_field const
sge::libpng::system::capabilities() const
{
	return
		image::capabilities_field(
			image::capabilities::threadsafe
		);
}

sge::media::extension_set const
sge::libpng::system::extensions() const
{
	return const_extensions;
}
