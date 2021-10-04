//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_FILE_HPP_INCLUDED
#define SGE_AUDIO_FILE_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sample_buffer_fwd.hpp>
#include <sge/audio/sample_container_fwd.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge::audio
{

/**
\brief Interface class for loaded audio files

For a short introduction to file loading, see \ref audio_example.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL file
{
	FCPPT_NONMOVABLE(
		file
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	file();
public:
	/**
	\brief Read \a _samples samples from the file, storing them in \a _destination.

	\param _samples Number of samples to read

	\param _destination The container to store the samples in. Samples will be \em appended to the container.

	\return The number of samples actually read. This might differ from \a _samples because EOF was reached (or for some other reason)
	*/
	[[nodiscard]]
	virtual
	sge::audio::sample_count
	// TODO(philipp): Return the buffer here?
	read(
		sge::audio::sample_count _samples,
		fcppt::reference<
			sge::audio::sample_buffer
		> _destination
	)
	= 0;

	/**
	\brief Read ALL the samples from the file.
	*/
	[[nodiscard]]
	virtual
	sge::audio::sample_container
	read_all() = 0;

	/**
	\brief How many samples will sge::audio::file::read probably return?

	The sge::audio::file::read function doesn't, in general, return as many
	samples as the user requests from it. That's because the file might be
	decoded in chunks, rather than single samples. This function returns an
	approximation of the chunk size (if any) of the file.

	You probably won't call this function directly. It is, however,
	important for streaming sounds, as it is a great help for caching.
	*/
	[[nodiscard]]
	virtual
	sge::audio::sample_count
	expected_package_size() const = 0;

	/// How many channels does this file hold
	[[nodiscard]]
	virtual
	sge::audio::channel_count
	channels() const = 0;

	/// What's the sample rate (in number of samples) of the file
	[[nodiscard]]
	virtual
	sge::audio::sample_rate
	sample_rate() const = 0;

	/// How many bits per sample are there
	[[nodiscard]]
	virtual
	sge::audio::bits_per_sample
	bits_per_sample() const = 0;

	/// Seek to the beginning of the file so you can read it again (for looping streaming sounds)
	virtual
	void
	reset() = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~file();
};

}

#endif
