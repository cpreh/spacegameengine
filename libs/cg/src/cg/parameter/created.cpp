//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/impl/parameter/convert_element_type.hpp>
#include <sge/cg/parameter/created.hpp>
#include <sge/cg/parameter/element_type.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::parameter::created::created(
	sge::cg::context::object const &_context,
	sge::cg::parameter::element_type const _element_type
)
:
	parameter_(
		::cgCreateParameter(
			_context.get(),
			sge::cg::impl::parameter::convert_element_type(
				_element_type
			)
		)
	)
{
	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgCreateParameter failed"),
		sge::cg::exception
	)
}

sge::cg::parameter::created::~created()
{
	::cgDestroyParameter(
		parameter_
	);
}

sge::cg::parameter::object
sge::cg::parameter::created::object() const
{
	return
		sge::cg::parameter::object(
			parameter_
		);
}

void
sge::cg::parameter::created::connect(
	sge::cg::parameter::named const &_named
)
{
	::cgConnectParameter(
		parameter_,
		_named.object().get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgConnectParameter failed"),
		sge::cg::exception
	)
}

void
sge::cg::parameter::created::disconnect( // NOLINT(readability-convert-member-functions-to-static)
	sge::cg::parameter::named const &_named
)
{
	::cgDisconnectParameter(
		_named.object().get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgDisconnectParameter failed"),
		sge::cg::exception
	)
}
