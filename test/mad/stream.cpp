#include "stream.hpp"
#include "frame.hpp"
#include <sge/raw_vector_impl.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/iconv.hpp>
#include <sge/log/headers.hpp>
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
	if (madstream.buffer != 0 && madstream.error != MAD_ERROR_BUFLEN)
		return;

	SGE_LOG_DEBUG(log::global(),log::_1 << "mad: syncing");

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
			log::global(),
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

	// we have to manually reset the error code, apparently
	madstream.error = static_cast<mad_error>(0);
}

sge::mad::frame_ptr const sge::mad::stream::decode()
{
	sync();

	frame_ptr f(new frame());

	if (!mad_frame_decode(&(f->madframe()),&madstream))
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: decoded frame successfully");

		return f;
	}

	if (MAD_RECOVERABLE(madstream.error))
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: got recoverable error: " << error_string() << ", decoding some more");

		return decode();
	}

	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "mad: got not recoverable error: "+error_string());

	if (madstream.error == MAD_ERROR_BUFLEN)
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: resyncing stream and decoding");

		return decode();
	}

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
