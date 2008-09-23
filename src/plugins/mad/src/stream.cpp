#include "../stream.hpp"
#include "../frame.hpp"
#include "../log.hpp"
#include <sge/raw_vector_impl.hpp>
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
	  input_buffer(input_size+mad_buffer_guard_size)
{
	mad_stream_init(&madstream);
}

void sge::mad::stream::sync()
{
	SGE_ASSERT(!stdstream.eof());

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
		throw audio::exception("mad: error reading from mpeg file");

	if (stdstream.eof())
	{
		SGE_LOG_DEBUG(
			log(),
			log::_1 << "mad: arrived at end of stream");

		byte_container::iterator guard_start = bytes.begin()+pos;
		std::fill(
			guard_start,
			guard_start+mad_buffer_guard_size,
			static_cast<byte_type>(0));
		pos += mad_buffer_guard_size;
	}

	input_buffer.swap(bytes);

	mad_stream_buffer(&madstream,&input_buffer[0],pos);
	madstream.error = MAD_ERROR_NONE;
}

sge::mad::frame &sge::mad::stream::decode()
{
	sync();

	if (!mad_frame_decode(&(f.madframe()),&madstream))
		return f;

	if (MAD_RECOVERABLE(madstream.error))
	{
		if (madstream.error != MAD_ERROR_LOSTSYNC || !stdstream.eof())
			return decode();

		return f;
	}

	if (madstream.error == MAD_ERROR_BUFLEN)
		return decode();

	throw audio::exception(
		SGE_TEXT("mad: unrecoverable error in mpeg stream: ")+error_string());
}

bool sge::mad::stream::eof() const
{
	return stdstream.eof();
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
	SGE_LOG_DEBUG(log(),log::_1 << "resetting file");
	mad_stream_finish(&madstream);
	mad_stream_init(&madstream);
	madstream.buffer = 0;
	stdstream.clear();
	stdstream.seekg(static_cast<std::streampos>(0));
	sync();
	SGE_LOG_DEBUG(log(),log::_1 << "file reset");
}
