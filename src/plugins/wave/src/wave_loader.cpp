// Own stuff
#include "../wave_file.hpp"
#include "../wave_loader.hpp"

sge::shared_ptr<sge::audio_file> sge::wave_loader::load(const std::string &filename)
{
	return sge::shared_ptr<sge::audio_file>(new wave_file(filename));
}

bool sge::wave_loader::is_valid_file(const std::string &filename) const
{
	try {
		wave_file file(filename);
	} catch (const audio_exception &e) {
		return false;
	}
	return true;
}
