//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_file_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::cg::program::from_file_parameters::from_file_parameters(
	sge::cg::context::object const &_context,
	sge::cg::program::source_type const _source_type,
	sge::cg::profile::object const &_profile,
	boost::filesystem::path const &_path,
	sge::cg::program::main_function const &_main_function,
	sge::cg::program::compile_options const &_compile_options
)
:
	context_(
		_context
	),
	source_type_(
		_source_type
	),
	profile_(
		_profile
	),
	path_(
		_path
	),
	main_function_(
		_main_function
	),
	compile_options_(
		_compile_options
	)
{
}

sge::cg::context::object const &
sge::cg::program::from_file_parameters::context() const
{
	return
		context_.get();
}

sge::cg::program::source_type
sge::cg::program::from_file_parameters::source_type() const
{
	return
		source_type_;
}

sge::cg::profile::object const &
sge::cg::program::from_file_parameters::profile() const
{
	return
		profile_.get();
}

boost::filesystem::path const &
sge::cg::program::from_file_parameters::path() const
{
	return
		path_;
}

sge::cg::program::main_function const &
sge::cg::program::from_file_parameters::main_function() const
{
	return
		main_function_;
}

sge::cg::program::compile_options const &
sge::cg::program::from_file_parameters::compile_options() const
{
	return
		compile_options_;
}
