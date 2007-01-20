#include <cerrno>
#include <locale>
#include <cassert>
#include <boost/array.hpp>
#include "../iconv.hpp"
#include "../types.hpp"
#include "../ucs4.hpp"

#ifdef SGE_LINUX_PLATFORM
#include <iconv.h>

namespace {

struct iconv_instance {
	iconv_t conv;

	iconv_instance(const std::string &from, const std::string &to) 
	 : conv(iconv_open(to.c_str(), from.c_str()))
	{
		if(conv == reinterpret_cast<iconv_t>(-1))
			throw sge::invalid_conversion(from,to);
	}

	~iconv_instance() {
		iconv_close(conv);
	}

	std::size_t convert(const char **inbuf, std::size_t *inbytes, char **outbuf, std::size_t *outbytes) {
		std::size_t bytesread = *inbytes;
		const std::size_t result = iconv(conv, const_cast<char**>(inbuf), inbytes, outbuf, outbytes);
		if(result == static_cast<std::size_t>(-1))
		{
			switch(errno) {
			case E2BIG:
				break;
			default:
				throw sge::conversion_failed();
			}
		}
		return bytesread - *inbytes;
	}
};

std::string encoding_to_string(const sge::encoding& to)
{
	using namespace sge;
	switch(to) {
	case enc_char_locale:
		return "UTF-8"; //FIXME
	case enc_utf8:
		return "UTF-8";
	case enc_ucs_4_internal:
		return "UCS-4";
	default:
		throw std::logic_error("Invalid encoding!");
	}
}

const sge::encoding internal_encoding = sge::enc_ucs_4_internal;

template<typename To, typename From>
To _iconv(const From& input, const sge::encoding from, const sge::encoding to, const typename To::allocator_type& alloc = typename To::allocator_type())
{
	iconv_instance ic(encoding_to_string(from), encoding_to_string(to));
	To output(alloc);
	
	const std::size_t buf_size = 512;
	boost::array<char,buf_size> arr;

	const char *ib = reinterpret_cast<const char*>(input.c_str());
	std::size_t in_size  = sizeof(typename From::value_type) * input.size();
	while(in_size)
	{
		std::size_t out_size = buf_size;
		char *ob = arr.c_array();
		ic.convert(&ib, &in_size, &ob, &out_size);

		const std::size_t bytes_written = buf_size - out_size;

		// FIXME why do we have to reverse the byteorder here?
		const std::size_t ucs4_bytes = sizeof(sge::uchar_t);
		assert(buf_size % ucs4_bytes == 0);
		for(char* p = arr.c_array(); p < &arr[bytes_written]; p += ucs4_bytes)
			std::reverse(p, p + ucs4_bytes);

		output += To(reinterpret_cast<typename To::const_pointer>(arr.data()), (bytes_written) / sizeof(typename To::value_type));
	}
	return output;
}

}

sge::ustring sge::iconv(const std::string& input, const encoding from, const ustring::allocator_type& alloc)
{
	return _iconv<ustring>(input, from, internal_encoding, alloc);
}

std::string sge::iconv(const ustring& input, const encoding to, const std::string::allocator_type& alloc)
{
	return _iconv<std::string>(input, internal_encoding, to, alloc);
}

#endif
