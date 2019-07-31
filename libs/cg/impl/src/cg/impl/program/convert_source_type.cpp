//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/impl/program/convert_source_type.hpp>
#include <sge/cg/program/source_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


CGenum
sge::cg::impl::program::convert_source_type(
	sge::cg::program::source_type const _type
)
{
	switch(
		_type
	)
	{
	case sge::cg::program::source_type::text:
		return CG_SOURCE;
	case sge::cg::program::source_type::binary:
		return CG_OBJECT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
