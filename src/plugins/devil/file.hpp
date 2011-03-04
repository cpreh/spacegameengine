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


#ifndef SGE_DEVIL_FILE_HPP_INCLUDED
#define SGE_DEVIL_FILE_HPP_INCLUDED

#include "file_fwd.hpp"
#include "image_holder.hpp"
#include "optional_error.hpp"
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/optional_extension.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <IL/il.h>

namespace sge
{
namespace devil
{

class file
:
	public sge::image2d::file
{
	FCPPT_NONCOPYABLE(
		file
	);
public:
	file();

	explicit file(
		image2d::view::const_object const &
	);

	~file();

	image2d::view::const_object const
	view() const;

	void
	data(
		image2d::view::const_object const &
	);

	image2d::dim const
	size() const;

	void
	save(
		fcppt::filesystem::path const &
	);

	devil::optional_error const
	load(
		fcppt::filesystem::path const &
	);

	devil::optional_error const
	load(
		sge::const_raw_range const &,
		sge::optional_extension const &
	);
private:
	typedef fcppt::function::object<
		devil::optional_error const ()
	> load_function;

	devil::optional_error const
	load_impl(
		load_function const &
	);

	void
	bind() const;

	ILenum
	format() const;

	devil::image_holder impl_;
};

}
}

#endif

