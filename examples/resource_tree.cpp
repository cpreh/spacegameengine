/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/media_path.hpp>
#include <sge/resource_tree/object.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef boost::filesystem::path resource;

resource const
path_to_resource(
	boost::filesystem::path const &_path
)
{
	fcppt::io::cout()
		<<
		fcppt::filesystem::path_to_string(
			_path
		)
		<<
		FCPPT_TEXT('\n');

	return
		_path;
}

}

int
main()
try
{
	typedef fcppt::random::generator::minstd_rand random_generator;

	random_generator generator(
		fcppt::random::generator::seed_from_chrono<
			random_generator::seed
		>()
	);

	typedef sge::resource_tree::object<
		resource,
		random_generator
	> resource_tree;

	resource_tree tree(
		sge::config::media_path(),
		resource_tree::path_to_resource_function(
			path_to_resource
		),
		generator
	);

	resource const example(
		tree.get(
			sge::resource_tree::path()
			/
			FCPPT_TEXT("images")
			/
			FCPPT_TEXT("grass")
		)
	);

	fcppt::io::cout()
		<<
		FCPPT_TEXT('\n')
		<<
		FCPPT_TEXT("Got resource example: ")
		<<
		fcppt::filesystem::path_to_string(
			example
		)
		<<
		FCPPT_TEXT('\n');
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
