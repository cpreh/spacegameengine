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


#include <sge/process/call.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerror.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/assert_message.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/select.h>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <cerrno>

namespace
{
void
exec(
	sge::process::argument_list const &_args)
{
	char **newargv = 
		new char*[
			static_cast<std::size_t>(
				_args.size()+1)];
	for(
		std::size_t i = 
			static_cast<std::size_t>(0); 
		i < _args.size(); 
		++i)
	{
		newargv[i] = 
			new char[
				static_cast<std::size_t>(
					_args[i].size()+1)];
		std::strcpy(
			newargv[i],
			_args[i].c_str());
	}
	newargv[
		static_cast<std::size_t>(
			_args.size())] = 0;

	execvp(
		_args.begin()->c_str(),
		newargv);

	throw 
		fcppt::exception(
			fcppt::string(
				FCPPT_TEXT("execvp failed: "))+
			fcppt::error::strerror(
				errno));
}
}

sge::process::output const
sge::process::call(
	argument_list const &_args)
{
	FCPPT_ASSERT_MESSAGE(
		!_args.empty(),
		FCPPT_TEXT("call needs at least the command name to execute"));

	std::size_t const
		reading_end = 
			static_cast<std::size_t>(
				0),
		writing_end = 
			static_cast<std::size_t>(
				1);

	int out_pipe[2];
	int err_pipe[2];

	if (pipe(out_pipe) == -1 || pipe(err_pipe) == -1)
		throw 
			fcppt::exception(
				FCPPT_TEXT("one of the pipes failed"));
	
	pid_t const pid = 
		fork();

	if (pid == 0)
	{
		close(
			out_pipe[reading_end]);
		close(
			err_pipe[reading_end]);
		dup2(
			out_pipe[writing_end],
			STDOUT_FILENO);
		dup2(
			err_pipe[writing_end],
			STDERR_FILENO);
		close(
			out_pipe[writing_end]);
		close(
			err_pipe[writing_end]);
		::exec(
			_args);
	}

	close(
		out_pipe[writing_end]);
	close(
		err_pipe[writing_end]);

	fd_set master_fds;
	FD_ZERO(
		&master_fds);
	
	FD_SET(
		out_pipe[reading_end],
		&master_fds);

	FD_SET(
		err_pipe[reading_end],
		&master_fds);

	fcppt::string output_stream,error_stream;
	exit_code exit_code_;
	int eof_count = 
		0;
	while (eof_count < 2)
	{
		fd_set read_fds = master_fds;

		int 
			maxfd = 
				std::max(
					out_pipe[reading_end],
					err_pipe[reading_end]),
			select_return = 
				select(
					maxfd+1,
					&read_fds,
					0,
					0,
					0);

		if (select_return == -1)
			throw 
				fcppt::exception(
					FCPPT_TEXT("select failed"));

		int const fds[2] = 
			{ 
				out_pipe[reading_end],
				err_pipe[reading_end] 
			};

		fcppt::string *outs[2] = 
			{
				&output_stream,
				&error_stream
			};
		for (int i = 0; i < 2; ++i)
		{
			if (!FD_ISSET(fds[i],&read_fds))
				continue;

			ssize_t const buffer_size = 
				static_cast<ssize_t>(
					1024);

			char char_buffer[buffer_size];

			ssize_t const b = ::read(
				fds[i],
				char_buffer,
				static_cast<std::size_t>(
					buffer_size-1));
			
			if (b == static_cast<ssize_t>(0))
			{
				eof_count++;
				FD_CLR(
					fds[i],
					&master_fds);
				continue;
			}
			
			if (b == static_cast<ssize_t>(-1))
				throw 
					fcppt::exception(
						FCPPT_TEXT("read failed"));

			outs[i]->insert(
				outs[i]->end(),
				char_buffer,
				char_buffer + b);
		}
	}
	
	waitpid(
		pid,
		(&exit_code_),
		0);
	
	return 
		output(
			output_stream,
			error_stream,
			exit_code_);
}
