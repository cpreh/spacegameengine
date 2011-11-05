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


#ifndef SGE_AUDIO_FILE_HPP_INCLUDED
#define SGE_AUDIO_FILE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/channel_type.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

/// Interface class for loaded audio files
/**
 * The file class is an interface class, you cannot instantiate it. Audio
 * loaders (wave, ogg) must derive from this class and create instances when a
 * file is loaded via sge::audio::loader::load or sge::audio::loader::load_raw.
 * For a short introduction to file loading, see \ref audio_example.
 */
class SGE_CLASS_SYMBOL file
{
	FCPPT_NONCOPYABLE(
		file
	);
protected:
	/// Dummy constructor so no instances of this base class can be created
	SGE_AUDIO_SYMBOL explicit
	file();
public:
	/// Read \a samples samples from the file, storing them in \a destination.
	/**
	 * \param samples Number of samples to read
	 * \param destination The container to store the samples in. Samples will be \em appended to the container.
	 * \returns The number of samples actually read. This might differ from \a samples because EOF was reached (or for some other reason)
	 */
	virtual audio::sample_count
	read(
		audio::sample_count samples,
		audio::sample_container &destination) = 0;

	/// Read ALL the samples from the file, storing them in \a destination.
	/**
	 * \param destination The container to store the samples in. Samples will be \em appended to the container.
	 * \returns The number of samples read.
	 */
	virtual audio::sample_count
	read_all(
		audio::sample_container &destination) = 0;

	/// How many samples will sge::audio::file::read probably return?
	/**
	 * The sge::audio::file::read function doesn't, in general, return as
	 * many samples as the user requests from it. That's because the file
	 * might be decoded in chunks, rather than single samples. This
	 * function returns an approximation of the chunk size (if any) of the
	 * file.
	 *
	 * You probably won't call this function directly. It is, however,
	 * important for streaming sounds, as it is a great help for caching
	 * stuff.
	 */
	virtual audio::sample_count
	expected_package_size() const = 0;

	/// How many channels does this file hold
	virtual audio::channel_type
	channels() const = 0;

	/// What's the sample rate (in number of samples) of the file
	virtual audio::sample_count
	sample_rate() const = 0;

	/// How many bits per sample are there
	virtual audio::sample_count
	bits_per_sample() const = 0;

	/// Seek to the beginning of the file so you can read it again (good for looping streaming sounds)
	virtual void
	reset() = 0;

	/// Calculate the bytes per sample
	SGE_AUDIO_SYMBOL
	audio::sample_count
	bytes_per_sample() const;

	/// Virtual dummy destructor to make it a class to safely derive from.
	/**
	 * Note that this destructor is pure virtual, but has an
	 * implementation. Strictly speaking, that's redundant. But it's safer
	 * for classes which otherwise don't have any pure virtual functions,
	 * yet should be abstract.
	 */
	SGE_AUDIO_SYMBOL
	virtual ~file() = 0;
};

}
}

#endif // AUDIO_FILE_HPP
