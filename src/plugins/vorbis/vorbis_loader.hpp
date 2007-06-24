#ifndef SGE_VORBIS_LOADER_HPP_INCLUDED
#define SGE_VORBIS_LOADER_HPP_INCLUDED

#include "../../audio/audio_loader/audio_loader.hpp"

namespace sge
{
class vorbis_loader : public audio_loader
{
	public:
	shared_ptr<audio_file> load(const std::string &);
	bool is_valid_file(const std::string &) const;
};
}

#endif // WAVE_HPP
