//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_CREATED_HPP_INCLUDED
#define SGE_CG_PARAMETER_CREATED_HPP_INCLUDED

#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/created_fwd.hpp>
#include <sge/cg/parameter/element_type_fwd.hpp>
#include <sge/cg/parameter/named_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace sge::cg::parameter
{

class created
{
	FCPPT_NONMOVABLE(
		created
	);
public:
	SGE_CG_DETAIL_SYMBOL
	created(
		sge::cg::context::object const &,
		sge::cg::parameter::element_type
	);

	SGE_CG_DETAIL_SYMBOL
	~created();

	[[nodiscard]]
	SGE_CG_DETAIL_SYMBOL
	sge::cg::parameter::object
	object() const;

	SGE_CG_DETAIL_SYMBOL
	void
	connect(
		sge::cg::parameter::named const &
	);

	SGE_CG_DETAIL_SYMBOL
	void
	disconnect(
		sge::cg::parameter::named const &
	);
private:
	CGparameter const parameter_; // NOLINT(misc-misplaced-const)
};

}

#endif
