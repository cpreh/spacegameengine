/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::openal::buffer::buffer(
	audio::file &_file
)
:
	holder_()
{
	audio::sample_container data;

	_file.read_all(
		data
	);

	FCPPT_LOG_DEBUG(
		openal::log(),
		fcppt::log::_
			<< FCPPT_TEXT("creating buffer of size ")
			<< data.size()
			<< FCPPT_TEXT(" and format ")
			<< openal::file_format(
				_file
			)
			<< FCPPT_TEXT(" and sample rate ")
			<< _file.sample_rate()
	);

	if(
		data.empty()
	)
		throw audio::exception(
			FCPPT_TEXT("tried to create empty nonstreaming sound, that's not possible!")
		);

	// TODO: this function is called more than once!
	::alBufferData(
		holder_.get(),
		openal::file_format(
			_file
		),
		data.data(),
		static_cast<
			ALsizei
		>(
			data.size()
		),
		static_cast<
			ALsizei
		>(
			_file.sample_rate()
		)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		audio::exception
	)
}

sge::audio::sound::positional_ptr const
sge::openal::buffer::create_positional(
	audio::sound::positional_parameters const &_param
)
{
	return 
		audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				openal::source
			>(
				_param,
				holder_.get()
			)
		);
}

sge::audio::sound::base_ptr const
sge::openal::buffer::create_nonpositional()
{
	return 
		audio::sound::base_ptr(
			fcppt::make_shared_ptr<
				openal::source
			>(
				holder_.get()
			)
		);
}

sge::openal::buffer::~buffer()
{
}
