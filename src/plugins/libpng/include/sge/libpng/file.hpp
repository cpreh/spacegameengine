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


#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include <sge/image/optional_path.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/config/external_begin.hpp>
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
	explicit file(
		std::istream &,
		sge::image::optional_path const &
	);

	explicit file(
		image2d::view::const_object const &
	);

	~file();

	image2d::view::const_object const
	view() const;

	image2d::dim const
	size() const;

	void
	save(
		fcppt::filesystem::path const &
	) const;
private:
	image2d::dim dim_;

	image::color::format::type format_;

	libpng::byte_vector bytes_;
};

}
}

#endif
