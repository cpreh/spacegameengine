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


#ifndef SGE_SRC_FONT_BITMAP_OBJECT_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_OBJECT_HPP_INCLUDED

#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/unit.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

class object
:
	public sge::font::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		boost::filesystem::path const &,
		sge::image2d::system &
	);

	~object();
private:
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	);

	sge::image::color::optional_format const
	color_format() const;

	typedef boost::ptr_vector<
		sge::image2d::file
	> image_vector;

	image_vector images_;

	sge::font::unit line_height_;

	sge::font::bitmap::char_map char_map_;

	sge::image::color::optional_format color_format_;
};

}
}
}

#endif
