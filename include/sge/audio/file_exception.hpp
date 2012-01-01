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


#ifndef SGE_AUDIO_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_AUDIO_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/optional_path.hpp>
#include <sge/audio/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace audio
{
/// Exception thrown when file-related operations fail.
/**
 * This exception might be thrown if a file is corrupted or there's no loader for
 * it available.
 */
class SGE_CLASS_SYMBOL file_exception
:
	public audio::exception
{
public:
	/// Initialize exception with an error string and an optional file path.
	/**
	 * The path is optional because there might be a file error but the
	 * path to the file is "lost" during the decoding process. It's still a
	 * file error, though.
	 */
	SGE_AUDIO_SYMBOL
	file_exception(
		optional_path const &,
		fcppt::string const &
	);
};
}
}

#endif
