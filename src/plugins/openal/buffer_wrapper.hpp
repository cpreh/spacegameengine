#ifndef SGE_OPENAL_BUFFER_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_WRAPPER_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "openal.hpp"

namespace sge
{
namespace audio
{
class file;
}

namespace openal
{
class buffer_wrapper : public boost::noncopyable
{
	public:
	buffer_wrapper(audio::file &);
	ALuint buffer() const;
	audio::file &file();
	audio::file const &file() const;
	void add_instance();
	bool remove_instance();

	private:
	audio::file &file_;
	ALuint buffer_;
	unsigned refcount_;
};
}
}

#endif
