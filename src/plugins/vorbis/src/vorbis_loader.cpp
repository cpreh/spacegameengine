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


// Own stuff
#include "../../../audio/audio_exception.hpp"
#include "../../../raw_vector_impl.hpp"
#include "../../../path.hpp"
#include "../vorbis_file.hpp"
#include "../vorbis_loader.hpp"

const sge::audio_file_ptr sge::vorbis_loader::load(const path &filename)
{
	return audio_file_ptr(new vorbis_file(filename, 16));
}

bool sge::vorbis_loader::is_valid_file(const path &filename) const
{
	try { 
		const vorbis_file file(filename, 16);
	} catch (const audio_exception &) {
		return false;
	}
	return true;
}
