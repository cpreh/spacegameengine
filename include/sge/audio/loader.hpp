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


#ifndef SGE_AUDIO_LOADER_HPP_INCLUDED
#define SGE_AUDIO_LOADER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/extension_set.hpp>
#include <sge/optional_extension.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace audio
{

/// Interface class for loaders
/**
 * The loader class is an interface class, you cannot instantiate it. Audio
 * loaders (wave, ogg) must derive from this class.
 *
 * For a short introduction to loading an audio file, see \ref audio_example.
 */
class SGE_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
protected:
	/** \protectedctor */
	SGE_AUDIO_SYMBOL explicit
	loader();
public:
	/// Load a file
	virtual audio::file_ptr const
	load(
		fcppt::filesystem::path const &
	) = 0;

	/// Load raw bytes
	/**
	 * \param r A range of bytes (can be discarded after this function completes)
	 * \param extension An optional extension indicating what (sub) type of file is inside
	 */
	virtual audio::file_ptr const
	load_raw(
		sge::const_raw_range const &r,
		sge::optional_extension const &extension
	) = 0;

	/// What capabilities this loader has. Is used in the sge::audio::multi_loader and in sge::systems to select a loader.
	virtual audio::loader_capabilities_field const
	capabilities() const = 0;

	/// What extensions this loader supports. Is used in the sge::audio::multi_loader and in sge::systems to select a loader.
	virtual sge::extension_set const
	extensions() const = 0;

	/** \virtualdtor */
	SGE_AUDIO_SYMBOL
	virtual ~loader() = 0;
};

}
}

#endif
