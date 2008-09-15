#ifndef SGE_OPENAL_SOURCE_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_WRAPPER_HPP_INCLUDED

#include "openal.hpp"

namespace sge
{
namespace openal
{
class source_wrapper
{
	public:
	source_wrapper();
	ALuint source() const { return source_; }
	void sync();
	~source_wrapper();
	private:
	ALuint source_;
	soudn_status::type status_;
};
}
}

#endif
