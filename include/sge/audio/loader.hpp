/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/optional_file_unique_ptr_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


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
class SGE_CORE_DETAIL_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
protected:
	/** \protectedctor */
	SGE_AUDIO_DETAIL_SYMBOL
	loader();
public:
	/**
	\brief Tries to load a file

	\return An empty file_unique_ptr on failure
	*/
	virtual
	sge::audio::optional_file_unique_ptr
	load(
		boost::filesystem::path const &
	) = 0;

	/// Load raw bytes
	/**
	 * \param range A range of bytes (can be discarded after this function completes)
	 * \param extension An optional extension indicating what (sub) type of file is inside
	 */
	virtual
	sge::audio::optional_file_unique_ptr
	load_raw(
		sge::media::const_raw_range const &range,
		sge::media::optional_extension const &extension
	) = 0;

	virtual
	sge::audio::optional_file_unique_ptr
	load_stream(
		std::istream &,
		sge::media::optional_extension const &extension
	) = 0;

	/// What extensions this loader supports. Is used in the sge::audio::multi_loader and in sge::systems to select a loader.
	virtual
	sge::media::extension_set
	extensions() const = 0;

	/** \virtualdtor */
	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~loader() = 0;
};

}
}

#endif
