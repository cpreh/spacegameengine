//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <filesystem>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::filesystem::path resource;

resource
path_to_resource(
	std::filesystem::path const &_path
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
