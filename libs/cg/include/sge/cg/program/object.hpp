//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PROGRAM_OBJECT_HPP_INCLUDED
#define SGE_CG_PROGRAM_OBJECT_HPP_INCLUDED

#include <sge/cg/string.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/named_fwd.hpp>
#include <sge/cg/parameter/optional_named_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/from_file_parameters_fwd.hpp>
#include <sge/cg/program/from_string_parameters_fwd.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace sge::cg::program
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_CG_DETAIL_SYMBOL
	explicit
	object(
		sge::cg::program::from_string_parameters const &
	);

	SGE_CG_DETAIL_SYMBOL
	explicit
	object(
		sge::cg::program::from_file_parameters const &
	);

	SGE_CG_DETAIL_SYMBOL
	~object();

	[[nodiscard]]
	SGE_CG_DETAIL_SYMBOL
	sge::cg::profile::object const &
	profile() const;

	[[nodiscard]]
	SGE_CG_DETAIL_SYMBOL
	sge::cg::parameter::named
	parameter(
		sge::cg::string const &
	) const;

	[[nodiscard]]
	SGE_CG_DETAIL_SYMBOL
	sge::cg::parameter::optional_named
	parameter_opt(
		sge::cg::string const &
	) const;

	[[nodiscard]]
	SGE_CG_DETAIL_SYMBOL
	CGprogram
	get() const;
private:
	sge::cg::profile::object const &profile_;

	CGprogram const program_; // NOLINT(misc-misplaced-const)
};

}

#endif
