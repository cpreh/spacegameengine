/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/noise/simplex/object.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iostream>
#include <fcppt/config/external_end.hpp>

awl::main::exit_code const
example_main(
	awl::main::function_context const &_main_function_context)
try
{
	typedef
	sge::noise::simplex::object<double,2>
	noise_type;

	noise_type noise_generator(128);

	fcppt::io::cout()
		<< FCPPT_TEXT("raw noise generator spit out: ")
		<< noise_generator.sample(
				noise_type::vector_type(
					23.0,
					42.0))
		<< FCPPT_TEXT('\n');

	typedef
	sge::noise::sample_parameters<noise_type>
	param_type;

	fcppt::io::cout()
		<< FCPPT_TEXT("noise generator spit out: ")
		<<
			sge::noise::sample(
				noise_generator,
				param_type(
					param_type::position_type(
						noise_type::vector_type(
							23.0,
							42.0)),
					param_type::amplitude_type(
						1.0),
					param_type::frequency_type(
						10.0),
					param_type::octaves_type(
						5u)))
		<< FCPPT_TEXT('\n');

	return awl::main::exit_success();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
