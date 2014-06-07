/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include <sge/image/optional_path_fwd.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/libpng/file_rep.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class file
:
	public sge::image2d::file
{
	FCPPT_NONCOPYABLE(
		file
	);
public:
	file(
		std::istream &,
		sge::image::optional_path const &
	);

	explicit
	file(
		sge::image2d::view::const_object const &
	);

	~file()
	override;
private:
	sge::image2d::view::const_object const
	view() const
	override;

	sge::image2d::dim const
	size() const
	override;

	void
	save(
		boost::filesystem::path const &
	) const
	override;

	void
	save_stream(
		std::ostream &
	) const
	override;

	sge::libpng::file_rep const rep_;
};

}
}

#endif
