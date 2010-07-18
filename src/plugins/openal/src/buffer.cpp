#include "../buffer.hpp"
#include "../source.hpp"
#include "../check_state.hpp"
#include "../file_format.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sound/base.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

sge::openal::buffer::buffer(
	audio::file_ptr const f)
{
	alGenBuffers(
		static_cast<ALsizei>(
			1),
		&buffer_);
	
	audio::sample_container data;
	f->read_all(
		data);

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("creating buffer of size ")
			<< data.size()
			<< FCPPT_TEXT(" and format ")
			<< file_format(*f)
			<< FCPPT_TEXT(" and sample rate ")
			<< f->sample_rate());

	if (data.empty())
		throw audio::exception(FCPPT_TEXT("tried to create empty nonstreaming sound, that's not possible!"));

	// TODO: this function is called more than once!
	alBufferData(
		buffer_,
		file_format(
			*f),
		data.data(),
		static_cast<ALsizei>(
			data.size()),
		static_cast<ALsizei>(
			f->sample_rate()));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		audio::exception
	)

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenBuffers failed"),
		audio::exception
	)
}

sge::audio::sound::positional_ptr const
sge::openal::buffer::create_positional(
	audio::sound::positional_parameters const&p)
{
	return 
		audio::sound::positional_ptr(
			new source(
				p,
				buffer_));
}

sge::audio::sound::base_ptr const
sge::openal::buffer::create_nonpositional()
{
	return 
		audio::sound::base_ptr(
			new source(
				buffer_));
}

sge::openal::buffer::~buffer()
{
	alDeleteBuffers(
		static_cast<ALsizei>(
			1),
		&buffer_);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alDeleteBuffers failed"),
		audio::exception
	)
}
