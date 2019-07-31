//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>


sge::cg::program::from_string_parameters::from_string_parameters(
	sge::cg::context::object const &_context,
	sge::cg::program::source_type const _source_type,
	sge::cg::profile::object const &_profile,
	sge::cg::program::source const &_source,
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
	source_(
		_source
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
sge::cg::program::from_string_parameters::context() const
{
	return
		context_.get();
}

sge::cg::program::source_type
sge::cg::program::from_string_parameters::source_type() const
{
	return
		source_type_;
}

sge::cg::profile::object const &
sge::cg::program::from_string_parameters::profile() const
{
	return
		profile_.get();
}

sge::cg::program::source const &
sge::cg::program::from_string_parameters::source() const
{
	return
		source_;
}

sge::cg::program::main_function const &
sge::cg::program::from_string_parameters::main_function() const
{
	return
		main_function_;
}

sge::cg::program::compile_options const &
sge::cg::program::from_string_parameters::compile_options() const
{
	return
		compile_options_;
}
