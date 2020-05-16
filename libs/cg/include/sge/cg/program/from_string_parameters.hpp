//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PROGRAM_FROM_STRING_PARAMETERS_HPP_INCLUDED
#define SGE_CG_PROGRAM_FROM_STRING_PARAMETERS_HPP_INCLUDED

#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_string_parameters_fwd.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace cg
{
namespace program
{

class from_string_parameters
{
public:
	SGE_CG_DETAIL_SYMBOL
	from_string_parameters(
		sge::cg::context::object const &,
		sge::cg::program::source_type,
		sge::cg::profile::object const &,
		sge::cg::program::source &&,
		sge::cg::program::main_function &&,
		sge::cg::program::compile_options &&
	);

	[[nodiscard]]
	sge::cg::context::object const &
	context() const;

	[[nodiscard]]
	sge::cg::program::source_type
	source_type() const;

	[[nodiscard]]
	sge::cg::profile::object const &
	profile() const;

	[[nodiscard]]
	sge::cg::program::source const &
	source() const;

	[[nodiscard]]
	sge::cg::program::main_function const &
	main_function() const;

	[[nodiscard]]
	sge::cg::program::compile_options const &
	compile_options() const;
private:
	fcppt::reference<
		sge::cg::context::object const
	> context_;

	sge::cg::program::source_type source_type_;

	fcppt::reference<
		sge::cg::profile::object const
	> profile_;

	sge::cg::program::source source_;

	sge::cg::program::main_function main_function_;

	sge::cg::program::compile_options compile_options_;
};

}
}
}

#endif
