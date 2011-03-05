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


#include "../loader.hpp"
#include "../file.hpp"
#include <sge/extension_set.hpp>
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <iterator>
#include <ios>

namespace
{

fcppt::char_type const *const supported_extension(
	FCPPT_TEXT("png")
);

sge::extension_set const extensions_((
	fcppt::assign::make_container<
		sge::extension_set
	>
	(
		supported_extension
	)
));

}

sge::libpng::loader::loader()
{
}

sge::libpng::loader::~loader()
{
}

sge::image2d::file_ptr const
sge::libpng::loader::load(
	fcppt::filesystem::path const &_path
)
{
	fcppt::io::cifstream file_stream(
		_path,
		std::ios::binary);
	if(!file_stream.is_open())
		throw image::file_exception(
			_path,
			FCPPT_TEXT("couldn't open file"));
	try
	{
		return
			fcppt::make_shared_ptr<
				file
			>(
				std::tr1::ref(
					file_stream),
				_path
			);
	}
	catch (
		sge::image::unsupported_format const &)
	{
		return sge::image2d::file_ptr();
	}
}

sge::image2d::file_ptr const
sge::libpng::loader::load(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
)
{
	if(
		_extension &&
		_extension
		!=
		sge::optional_extension(
			supported_extension
		)
	)
		return sge::image2d::file_ptr();

	typedef
	boost::iostreams::stream<boost::iostreams::array_source>
	stream_type;

	stream_type raw_stream(
		reinterpret_cast<boost::iostreams::array_source::char_type const *>(
			_range.begin()),
		reinterpret_cast<boost::iostreams::array_source::char_type const *>(
			_range.end()));
	
	try
	{
		return 
			fcppt::make_shared_ptr<
				file
			>(
				std::tr1::ref(
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
sge::libpng::loader::create(
	image2d::view::const_object const &_view
)
{
	return
		fcppt::make_shared_ptr<
			file
		>(
			_view
		);
}

sge::image::capabilities_field const
sge::libpng::loader::capabilities() const
{
	return
		image::capabilities_field(
			image::capabilities::threadsafe
		);
}

sge::extension_set const
sge::libpng::loader::extensions() const
{
	return extensions_;
}
