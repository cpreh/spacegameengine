#ifndef SGE_OPENAL_SOURCE_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_WRAPPER_HPP_INCLUDED

#include "openal.hpp"
#include <sge/noncopyable.hpp>

namespace sge
{
namespace openal
{
class source_wrapper
{
SGE_NONCOPYABLE(source_wrapper)

public:
	source_wrapper();
	~source_wrapper();

	ALuint value_;
};
}
}

#endif
