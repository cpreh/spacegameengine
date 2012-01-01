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


#ifndef SGE_DEVIL_FILE_HPP_INCLUDED
#define SGE_DEVIL_FILE_HPP_INCLUDED

#include <sge/devil/file_fwd.hpp>
#include <sge/devil/image_holder.hpp>
#include <sge/devil/optional_error.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <fcppt/config/external_end.hpp>


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

	image2d::dim const
	size() const;

	void
	save(
		fcppt::filesystem::path const &
	) const;

	devil::optional_error const
	load(
		fcppt::filesystem::path const &
	);

	devil::optional_error const
	load(
		sge::media::const_raw_range const &,
		sge::media::optional_extension const &
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

