#ifndef SGE_OPENAL_BUFFER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HPP_INCLUDED

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
class buffer : public boost::noncopyable
{
	public:
	buffer(audio::file &);
	ALuint albuffer() const { return buffer_; }
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
