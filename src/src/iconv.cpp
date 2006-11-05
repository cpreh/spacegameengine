#include "../iconv.hpp"
#include "../types.hpp"
#include <cerrno>
#include <locale>

#ifdef SGE_LINUX_PLATFORM
#include <iconv.h>

namespace {

struct iconv_instance {
	iconv_t conv;

	iconv_instance(const std::string &from, const std::string &to) {
		conv = iconv_open (to.c_str(), from.c_str());
		if (conv == reinterpret_cast<iconv_t>(-1))
			throw sge::invalid_conversion(from,to);
	}

	~iconv_instance() {
		iconv_close(conv);
	}

	std::size_t convert(const char **inbuf, std::size_t *inbytes, char **outbuf, std::size_t *outbytes) {
		std::size_t bytesread = *inbytes;
		std::size_t result = iconv(conv, const_cast<char**>(inbuf), inbytes, outbuf, outbytes);
		if ((result == static_cast<std::size_t>(-1)) && (errno == EINVAL))
			throw sge::conversion_failed();
		return bytesread - *inbytes;
	}
};

std::string encoding_to_string(const sge::encoding& to)
{
	using namespace sge;
	switch(to) {
	case enc_char_locale:
		return std::locale().name();
	case enc_utf8:
		return "UTF-8";
	case enc_ucs_4_internal:
		return "UCS-4-INTERNAL";
	default:
		throw std::logic_error("Invalid encoding!");
	}
}

const sge::encoding internal_encoding = sge::enc_ucs_4_internal;

template<typename To, typename From>
To _iconv(const From& input, const sge::encoding from, const sge::encoding to)
{
	iconv_instance ic(encoding_to_string(from), encoding_to_string(to));
	To output;
	
	const std::size_t buf_size = 512;
	char arr[buf_size];

	const char *ib = reinterpret_cast<const char*>(input.c_str());
	std::size_t in_size  = sizeof(typename From::value_type) * input.size();
	while(in_size)
	{
		std::size_t out_size = buf_size;
		char *ob = arr;
		ic.convert(&ib, &in_size, &ob, &out_size);
		output += To(reinterpret_cast<typename To::const_pointer>(&arr[0]), (buf_size - out_size) / sizeof(typename To::value_type));
	}
	return output;
}

}

sge::ustring sge::iconv(const std::string& input, const encoding from)
{
	return _iconv<ustring>(input, from, internal_encoding);
}

std::string sge::iconv(const ustring& input, const encoding to)
{
	return _iconv<std::string>(input, internal_encoding, to);
}

#endif
