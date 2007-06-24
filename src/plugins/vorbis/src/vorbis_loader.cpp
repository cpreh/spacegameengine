// Own stuff
#include "../../../audio/audio_exception.hpp"
#include "../vorbis_file.hpp"
#include "../vorbis_loader.hpp"

sge::shared_ptr<sge::audio_file> sge::vorbis_loader::load(const std::string &filename)
{
	return sge::shared_ptr<sge::audio_file>(new vorbis_file(filename,16));
}

bool sge::vorbis_loader::is_valid_file(const std::string &filename) const
{
	try { 
		vorbis_file file(filename,16);
	} catch (const audio_exception &e) {
		return false;
	}
	return true;
}
