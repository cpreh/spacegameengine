//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/info/get_version.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version.hpp>
#include <sge/opengl/info/version_type.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/expect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


sge::opengl::info::version
sge::opengl::info::get_version(
	sge::opengl::backend::current const &
)
{
	std::istringstream input(
		sge::opengl::get_string(
			GL_VERSION
		)
	);

	sge::opengl::info::version_type major{};

	sge::opengl::info::version_type minor{};

	input >> major;

	fcppt::io::expect(
		input,
		'.'
	);

	input >> minor;

	if(
		!input
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Getting GL_VERSION failed")
			};
	}

	return
		sge::opengl::info::version{
			sge::opengl::info::major_version{
				major
			},
			sge::opengl::info::minor_version{
				minor
			}
		};
}
