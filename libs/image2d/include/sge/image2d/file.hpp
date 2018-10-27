/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE2D_FILE_HPP_INCLUDED
#define SGE_IMAGE2D_FILE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/file_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL file
{
	FCPPT_NONCOPYABLE(
		file
	);
protected:
	SGE_IMAGE2D_DETAIL_SYMBOL
	file();
public:
	virtual
	sge::image2d::view::const_object
	view() const = 0;

	virtual
	sge::image2d::dim
	size() const = 0;

	virtual
	void
	save(
		boost::filesystem::path const &
	) const = 0;

	virtual
	void
	save_stream(
		std::ostream &
	) const = 0;

	SGE_IMAGE2D_DETAIL_SYMBOL
	virtual
	~file();
};

}
}

#endif
