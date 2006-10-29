#include "../iconv.hpp"
#include "../types.hpp"
#include <cerrno>
#include <boost/scoped_array.hpp>


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
		return
			bytesread - *inbytes;
	}
};

sge::string encoding_to_string(const encoding& to)
{
	switch(to) {
	case enc_utf8:
		return "UTF-8";
	case enc_ucs_4_internal:
		return "UCS-4-INTERNAL";
	default:
		throw std::logic_error("Invalid encoding!");
	}
}

}

// defined from iconv.h
#undef iconv

const char* const internal_encoding = "UCS-4-INTERNAL";

void sge::iconv(const ustring& input, string& output, const encoding to)
{
	output.clear();
	iconv_instance ic(internal_encoding, encoding_to_string(to));
	std::size_t len = 1;
	while(len)
	{
		const std::size_t buf_size = 512;
		boost::scoped_array<char> arr(new char[buf_size]);
		std::size_t in_size  = sizeof(uchar_t) * input.size();
		std::size_t out_size = sizeof(char   ) * len;
		const char *ib = reinterpret_cast<const char*>(input.c_str());
		      char *ob = reinterpret_cast<      char*>(arr.get());
		std::size_t res = ic.convert(&ib, &in_size, &ob, &out_size);
		len = res / sizeof(uchar_t);
		output += string(arr.get(), buf_size - out_size);
	}
}

#endif
