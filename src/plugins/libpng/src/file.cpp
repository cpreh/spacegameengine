/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/const_raw_pointer.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/file_rep_from_stream.hpp>
#include <sge/libpng/file_rep_from_view.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <sge/libpng/write.hpp>
#include <sge/media/optional_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <ios>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::libpng::file::file(
	std::istream &_stream,
	sge::media::optional_path const &_path
)
:
	rep_(
		sge::libpng::file_rep_from_stream(
			_stream,
			_path
		)
	)
{
}

sge::libpng::file::file(
	sge::image2d::view::const_object const &_view
)
:
	rep_(
		sge::libpng::file_rep_from_view(
			_view
		)
	)
{
}

sge::libpng::file::~file()
{
}

sge::image2d::view::const_object const
sge::libpng::file::view() const
{
	return
		sge::image2d::view::make_const(
			fcppt::cast::to_char_ptr<
				sge::image::const_raw_pointer
			>(
				rep_.bytes().data()
			),
			this->size(),
			sge::libpng::to_sge_format(
				rep_.format()
			),
			sge::image2d::pitch::null()
		);
}

sge::image2d::dim const
sge::libpng::file::size() const
{
	return
		rep_.size();
}

void
sge::libpng::file::save(
	boost::filesystem::path const &_path
) const
{
	boost::filesystem::ofstream output(
		_path,
		std::ios_base::binary
	);

	if(
		!output.is_open()
	)
		throw
			sge::image2d::file_exception(
				sge::media::optional_path(
					_path
				),
				FCPPT_TEXT("couldn't open file")
			);

	sge::libpng::write(
		output,
		sge::media::optional_path(
			_path
		),
		rep_
	);
}

void
sge::libpng::file::save_stream(
	std::ostream &_stream
) const
{
	sge::libpng::write(
		_stream,
		sge::media::optional_path(),
		rep_
	);
}
