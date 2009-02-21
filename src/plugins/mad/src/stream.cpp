#include "../stream.hpp"
#include "../frame.hpp"
#include "../log.hpp"
#include <sge/container/raw_vector_impl.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/assert.hpp>
#include <sge/iconv.hpp>
#include <sge/audio/exception.hpp>
#include <istream>
#include <algorithm>
#include <cstddef>

sge::mad::stream::size_type const sge::mad::stream::input_size = 
	static_cast<size_type>(5*8192);

sge::mad::stream::size_type const sge::mad::stream::mad_buffer_guard_size = 
	static_cast<size_type>(MAD_BUFFER_GUARD);

sge::mad::stream::stream(std::istream &stdstream)
	: stdstream(stdstream),
	  input_buffer(input_size+mad_buffer_guard_size),
		eof_(false)
{
	mad_stream_init(&madstream);
}

void sge::mad::stream::sync()
{
	if (madstream.buffer != 0 && madstream.error != MAD_ERROR_BUFLEN)
		return;

	byte_container bytes(input_size+mad_buffer_guard_size);

	// keeps track of the current stream position
	size_type pos = static_cast<size_type>(0);

	if (madstream.next_frame)
	{
		std::copy(madstream.next_frame,madstream.bufend,bytes.begin());
		pos = static_cast<size_type>(madstream.bufend-madstream.next_frame);
	}
	
	stdstream.read(
		// istream uses char, mad uses unsigned char, so cast here
		reinterpret_cast<char*>(&bytes[pos]),
		static_cast<std::streamsize>(input_size-pos));
	
	pos += static_cast<size_type>(stdstream.gcount());

	if (stdstream.bad())
		throw audio::exception(
			SGE_TEXT("mad: error reading from mpeg file"));

	if (stdstream.eof())
	{
		SGE_LOG_DEBUG(
			log(),
			log::_1 << SGE_TEXT("arrived at end of stream"));

		byte_container::iterator guard_start = bytes.begin()+pos;
		std::fill(
			guard_start,
			guard_start+mad_buffer_guard_size,
			static_cast<byte_type>(0));
		pos += mad_buffer_guard_size;
	}

	input_buffer.swap(bytes);

	mad_stream_buffer(&madstream,input_buffer.data(),pos);
	madstream.error = MAD_ERROR_NONE;
}

/*
 * why decoding_mode? when decoding, the first frame decides if the file read
 * is a valid mpeg file or if it's garbage - with one exception. if the first
 * frame begins with "ID3" then it _could_ be a valid mpeg file, we don't know.
 *
 * currently, we just assume that it _is_ a valid mpeg file because if it
 * _isn't_, we have to load the _complete_ file until we know for sure if it's
 * valid or not.
 *
 * if there's no id3 tag, we decode with "strict". if there are no recoverable
 * errors (like BAD_BITRATE or something), we've got a valid mpeg file. if
 * there are errors, we throw an exception
 */
sge::mad::frame &sge::mad::stream::decode(decoding_mode::type const mode)
{
	sync();

	if (!mad_frame_decode(&(f.madframe()),&madstream))
		return f;
	
	if (mode == decoding_mode::strict)
	{
		SGE_LOG_DEBUG(
			log(),
			log::_1
				<< SGE_TEXT("mad: got decoder error ")
				<< static_cast<unsigned>(madstream.error)
				<< SGE_TEXT(" and in strict mode, so exiting"));
		throw audio::exception(
			SGE_TEXT("mad: first frame resulted in an error: ")
			+ error_string());
	}

	// we just need more data, not really an error
	if (madstream.error == MAD_ERROR_BUFLEN)
	{
		SGE_LOG_DEBUG(
			log(),
			log::_1 << SGE_TEXT("got buflen error, decoding some more"));
		return decode(decoding_mode::recover);
	}

	// if we lost synchronization _and_ we're at the end of the file, then really
	// no error occured, it's just...mad
	if (madstream.error == MAD_ERROR_LOSTSYNC && stdstream.eof())
	{
		eof_ = true;
		return f;
	}
	
	if (MAD_RECOVERABLE(madstream.error))
		return decode(decoding_mode::recover);

	// the error is really an error and it's not recoverable from
	throw audio::exception(
		SGE_TEXT("mad: unrecoverable error in mpeg stream: ")
		+error_string());
}

bool sge::mad::stream::eof() const
{
	return eof_;
}

sge::mad::stream::~stream()
{
	mad_stream_finish(&madstream);
}

sge::string const sge::mad::stream::error_string() const
{
	return sge::iconv(mad_stream_errorstr(&madstream));
}

void sge::mad::stream::reset()
{
	SGE_LOG_DEBUG(
		log(),
		log::_1 << SGE_TEXT("resetting file"));
	mad_stream_finish(&madstream);
	mad_stream_init(&madstream);
	madstream.buffer = 0;
	stdstream.clear();
	stdstream.seekg(static_cast<std::streampos>(0));
	sync();
	SGE_LOG_DEBUG(
		log(),
		log::_1 << SGE_TEXT("file reset"));
}
