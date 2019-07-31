//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/const_raw_pointer.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <sge/libpng/write.hpp>
#include <sge/media/name.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <ios>
#include <iosfwd>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::file::file(
	fcppt::log::object &_log,
	sge::libpng::file_rep &&_rep
)
:
	log_{
		_log
	},
	rep_(
		std::move(
			_rep
		)
	)
{
}

sge::libpng::file::~file()
{
}

sge::image2d::view::const_object
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
			fcppt::math::dim::null<
				sge::image2d::pitch
			>()
		);
}

sge::image2d::dim
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

	sge::media::optional_name const name{
		sge::media::name{
			fcppt::filesystem::path_to_string(
				_path
			)
		}
	};

	if(
		!output.is_open()
	)
		throw
			sge::image2d::file_exception(
				name,
				FCPPT_TEXT("couldn't open file")
			);

	sge::libpng::write(
		log_,
		output,
		name,
		rep_
	);
}

void
sge::libpng::file::save_stream(
	std::ostream &_stream
) const
{
	sge::libpng::write(
		log_,
		_stream,
		sge::media::optional_name(),
		rep_
	);
}
