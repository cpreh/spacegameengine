//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/buffer.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/file_format.hpp>
#include <sge/openal/source.hpp>
#include <sge/openal/funcs/buffer_data.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::openal::buffer::buffer(
	fcppt::log::object &_log,
	sge::audio::file &_file
)
:
	log_{
		_log
	},
	holder_{
		_log
	}
{
	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<< FCPPT_TEXT("Reading a whole file into a buffer")
	)

	sge::audio::sample_container data(
		_file.read_all()
	);

	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("creating buffer of size ")
			<<
			data.size()
			<<
			FCPPT_TEXT(" and format ")
			<<
			sge::openal::file_format(
				_file
			)
			<<
			FCPPT_TEXT(" and sample rate ")
			<<
			_file.sample_rate()
	)

	if(
		data.empty()
	)
		throw
			sge::audio::exception{
				FCPPT_TEXT("tried to create empty nonstreaming sound, that's not possible!")
			};

	sge::openal::funcs::buffer_data(
		holder_.get(),
		sge::openal::file_format(
			_file
		),
		data.data(),
		fcppt::cast::size<
			ALsizei
		>(
			fcppt::cast::to_signed(
				data.size()
			)
		),
		fcppt::cast::size<
			ALsizei
		>(
			fcppt::cast::to_signed(
				_file.sample_rate().get()
			)
		)
	);
}

sge::audio::sound::positional_unique_ptr
sge::openal::buffer::create_positional(
	sge::audio::sound::positional_parameters const &_param
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::positional
		>(
			fcppt::make_unique_ptr<
				sge::openal::source
			>(
				log_,
				_param,
				holder_.get()
			)
		);
}

sge::audio::sound::base_unique_ptr
sge::openal::buffer::create_nonpositional(
	sge::audio::sound::nonpositional_parameters const &_param
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::base
		>(
			fcppt::make_unique_ptr<
				sge::openal::source
			>(
				log_,
				_param,
				holder_.get()
			)
		);
}

sge::openal::buffer::~buffer()
{
}
