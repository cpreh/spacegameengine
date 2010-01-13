/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_FILE_HPP_INCLUDED
#define SGE_IMAGE_FILE_HPP_INCLUDED

#include <sge/image/file_fwd.hpp>
#include <sge/image/dim_type.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace image
{

class SGE_CLASS_SYMBOL file
{
	FCPPT_NONCOPYABLE(file)
protected:
	SGE_SYMBOL file();
public:
	virtual void
	data(
		view::const_object const &
	) = 0;

	virtual view::const_object const
	view() const = 0;

	virtual dim_type const
	dim() const = 0;

	virtual void
	save(
		fcppt::filesystem::path const &
	) = 0;

	SGE_SYMBOL virtual ~file();
};

}
}

#endif
