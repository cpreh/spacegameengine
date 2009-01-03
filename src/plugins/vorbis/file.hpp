#ifndef SGE_VORBIS_FILE_HPP_INCLUDED
#define SGE_VORBIS_FILE_HPP_INCLUDED

#include <sge/audio/file.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/file.hpp>
#include <boost/filesystem/fstream.hpp>
#include <vorbis/vorbisfile.h>
#include <cstddef>

namespace sge
{
namespace vorbis
{
class file : public audio::file
{
	public:
	typedef audio::sample_count sample_count;
	typedef audio::channel_type channel_type;
	typedef audio::sample_container sample_container;

	explicit file(
		filesystem::path const &);
	sample_count read(sample_count samples, sample_container &);
	sample_count read_all(sample_container &);

	channel_type channels() const;
	sample_count sample_rate() const;
	sample_count bits_per_sample() const;
	void reset();

	~file();

	private:
	string const                file_name;
	boost::filesystem::ifstream stdstream;
	OggVorbis_File              ogg_file;
	channel_type                channels_;
	sample_count                sample_rate_;

	// ogg callbacks
	static std::size_t ogg_read_static(void *ptr, std::size_t size, std::size_t nmemb, void *datasource);
	static int ogg_seek_static(void *datasource, ogg_int64_t offset, int whence);
	static int ogg_close_static(void *datasource);
	static long ogg_tell_static(void *datasource);

	std::size_t ogg_read(void *ptr, std::size_t size, std::size_t nmemb);
	int ogg_seek(ogg_int64_t offset, int whence);
	int ogg_close();
	long ogg_tell();
};
}
}

#endif
