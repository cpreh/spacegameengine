/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../wave_file.hpp"
#include "../wave_loader.hpp"
#include <sge/raw_vector_impl.hpp>

const sge::audio_file_ptr sge::wave_loader::load(const path &filename)
{
	return audio_file_ptr(new wave_file(filename));
}

bool sge::wave_loader::is_valid_file(const path &filename) const
{
	try {
		const wave_file file(filename);
	} catch (const audio_exception &) {
		return false;
	}
	return true;
}
