#ifndef SGE_AUDIO_EXCEPTION_HPP_INCLUDED
#define SGE_AUDIO_EXCEPTION_HPP_INCLUDED

// C++
#include <string>
// sge
#include "../exception.hpp"

namespace sge
{
struct audio_exception : public exception 
{
	audio_exception(const std::string &s) : exception(s) {}
};
}

#endif // AUDIO_EXCEPTION_HPP
