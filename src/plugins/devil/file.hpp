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


#ifndef SGE_DEVIL_FILE_HPP_INCLUDED
#define SGE_DEVIL_FILE_HPP_INCLUDED

#include "image_impl.hpp"
#include <sge/image/file.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace devil
{

class file
:
	public image::file
{
public:
	explicit file(
		fcppt::filesystem::path const &
	);

	explicit file(
		image::view::const_object const &
	);

	image::view::const_object const
	view() const;

	void
	data(
		image::view::const_object const &
	);

	image::dim_type const
	dim() const;

	void
	save(
		fcppt::filesystem::path const &
	);
private:
	void
	bind_me() const;

	void
	load(
		fcppt::filesystem::path const &
	);

	ILint
	format() const;

	image_impl impl_;
};

}
}

#endif

