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


#ifndef SGE_LIBPNG_SYSTEM_HPP_INCLUDED
#define SGE_LIBPNG_SYSTEM_HPP_INCLUDED

#include <sge/image/optional_path_fwd.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class system
:
	public sge::image2d::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system()
	override;

	sge::image2d::optional_file_unique_ptr
	load(
		boost::filesystem::path const &
	)
	override;

	sge::image2d::optional_file_unique_ptr
	load_raw(
		sge::media::const_raw_range const &,
		sge::media::optional_extension const &
	)
	override;

	sge::image2d::optional_file_unique_ptr
	load_stream(
		std::istream &,
		sge::media::optional_extension const &
	)
	override;

	sge::image2d::optional_file_unique_ptr
	create(
		sge::image2d::view::const_object const &,
		sge::media::optional_extension const &
	)
	override;

	sge::media::extension_set
	extensions() const
	override;
private:
	sge::image2d::optional_file_unique_ptr
	load_impl(
		std::istream &,
		sge::image::optional_path const &
	);
};

}
}

#endif
