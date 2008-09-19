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
	// madstream.buffer == 0 means the stream has no buffer yet
	if (madstream.buffer != 0 && madstream.error != MAD_ERROR_BUFLEN)
	{
		//SGE_LOG_DEBUG(log::global(),log::_1 << "mad: syncing not needed");
		return;
	}

	//SGE_LOG_DEBUG(log::global(),log::_1 << "mad: stream needs syncing");
	
	byte_container bytes(input_size+mad_buffer_guard_size);

	// keeps track of the current stream position
	size_type pos = static_cast<size_type>(0);

	if (madstream.next_frame)
	{
		//SGE_LOG_DEBUG(log::global(),log::_1 << "mad: stream not fully consumed");
		std::copy(madstream.next_frame,madstream.bufend,bytes.begin());
		pos = static_cast<size_type>(madstream.bufend-madstream.next_frame);
	}

	/*
	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "mad: reading " << static_cast<std::streamsize>(input_size-pos) 
		        << " bytes from file, starting at " << pos);
	*/
	
	stdstream.read(
		// istream uses char, mad uses unsigned char, so cast here
		reinterpret_cast<char*>(&bytes[pos]),
		static_cast<std::streamsize>(input_size-pos));

	/*
	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "mad: read " << stdstream.gcount() << " bytes from file");
	*/
	
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

	input_buffer = bytes;
	//input_buffer.swap(bytes);

	/*
	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "mad: setting stream buffer, size " << pos);
	*/

	mad_stream_buffer(&madstream,&input_buffer[0],pos);

	// we have to manually reset the error code, apparently
	madstream.error = static_cast<mad_error>(0);
}

void sge::mad::stream::decode(frame &f)
{
	sync();

	/*
	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "mad: decoding a frame");
	*/

	if (!mad_frame_decode(&(f.madframe()),&madstream))
	{
		/*
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: decoded frame successfully");
		*/
		return;
	}
	
	if (MAD_RECOVERABLE(madstream.error))
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: got recoverable error: " << error_string() << ", decoding some more");

		decode(f);
	}
	else
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "mad: got not recoverable error: "+error_string());

		if (madstream.error == MAD_ERROR_BUFLEN)
		{
			SGE_LOG_DEBUG(
				log::global(),
				log::_1 << "mad: resyncing stream and decoding");

			sync();
			decode(f);
		}
		else
		{
			throw audio::exception(
				SGE_TEXT("mad: unrecoverable error in mpeg stream: ")+error_string());
		}
	}
	/*
	if (madstream.error == MAD_ERROR_BUFLEN)
	{
		SGE_LOG_INFO(
			log::global(),
			log::_1 << SGE_TEXT("mad: got buflen error, so retrieving more bytes"));
		sync();
		decode(f);
		return;
	}

	if (madstream.error == MAD_ERROR_LOSTSYNC && stdstream.eof())
	{
		SGE_LOG_INFO(
			log::global(),
			log::_1 << SGE_TEXT("mad: lost sync, but at end of file "));
		return;
	}
	
	if (!MAD_RECOVERABLE(madstream.error))
		throw audio::exception(
			SGE_TEXT("mad: unrecoverable error in mpeg stream: ")+error_string());
	
	SGE_LOG_WARNING(
		log::global(),
		log::_1 << SGE_TEXT("mad: got recoverable error: "+error_string()));
	*/
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
