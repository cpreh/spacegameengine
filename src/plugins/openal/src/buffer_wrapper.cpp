#include "../buffer_wrapper.hpp"
#include "../error.hpp"
#include <sge/audio/loader/file.hpp>

sge::openal::buffer_wrapper::buffer_wrapper(audio::file &file_)
	: file_(file_),refcount_(static_cast<unsigned>(1))
{
	alGenBuffers(static_cast<ALsizei>(1),&buffer_);
	SGE_OPENAL_ERROR_CHECK
}

ALuint sge::openal::buffer_wrapper::buffer() const
{
	return buffer_;
}

sge::audio::file &sge::openal::buffer_wrapper::file()
{
	return file_;
}

sge::audio::file const &sge::openal::buffer_wrapper::file() const
{
	return file_;
}

void sge::openal::buffer_wrapper::add_instance()
{
	refcount_++;
}	

bool sge::openal::buffer_wrapper::remove_instance()
{
	if (--refcount_ != static_cast<unsigned>(0))
		return false;

	alDeleteBuffers(static_cast<ALsizei>(1),&buffer_);
	SGE_OPENAL_ERROR_CHECK
	return true;
}
