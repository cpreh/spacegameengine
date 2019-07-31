//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/check_state_listing.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/to_fcppt_string.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/impl/program/convert_source_type.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/cg/parameter/optional_named.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/from_file_parameters.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/object.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace
{

void
assert_program(
	sge::cg::context::object const &,
	CGprogram,
	fcppt::string
);

}

sge::cg::program::object::object(
	sge::cg::program::from_string_parameters const &_parameters
)
:
	profile_(
		_parameters.profile()
	),
	program_(
		::cgCreateProgram(
			_parameters.context().get(),
			sge::cg::impl::program::convert_source_type(
				_parameters.source_type()
			),
			_parameters.source().get().c_str(),
			profile_.get(),
			_parameters.main_function().get().c_str(),
			_parameters.compile_options().pointers().data()
		)
	)
{
	::assert_program(
		_parameters.context(),
		program_,
		FCPPT_TEXT("cgCreateProgram")
	);
}

sge::cg::program::object::object(
	sge::cg::program::from_file_parameters const &_parameters
)
:
	profile_(
		_parameters.profile()
	),
	program_(
		::cgCreateProgramFromFile(
			_parameters.context().get(),
			sge::cg::impl::program::convert_source_type(
				_parameters.source_type()
			),
			_parameters.path().string().c_str(),
			profile_.get(),
			_parameters.main_function().get().c_str(),
			_parameters.compile_options().pointers().data()
		)
	)
{
	::assert_program(
		_parameters.context(),
		program_,
		FCPPT_TEXT("cgCreateProgramFromFile")
	);
}

sge::cg::program::object::~object()
{
	::cgDestroyProgram(
		program_
	);
}

sge::cg::profile::object const &
sge::cg::program::object::profile() const
{
	return
		profile_;
}

sge::cg::parameter::named
sge::cg::program::object::parameter(
	sge::cg::string const &_name
) const
{
	return
		fcppt::optional::to_exception(
			this->parameter_opt(
				_name
			),
			[
				&_name
			]{
				return
					sge::cg::exception(
						FCPPT_TEXT("Parameter with name '")
						+
						sge::cg::to_fcppt_string(
							_name
						)
						+
						FCPPT_TEXT("' not found")
					);
			}
		);
}

sge::cg::parameter::optional_named
sge::cg::program::object::parameter_opt(
	sge::cg::string const &_name
) const
{
	CGparameter const ret(
		::cgGetNamedParameter(
			this->get(),
			_name.c_str()
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetNamedParameter failed"),
		sge::cg::exception
	)

	return
		ret
		==
		nullptr
		?
			sge::cg::parameter::optional_named()
		:
			sge::cg::parameter::optional_named(
				sge::cg::parameter::named(
					sge::cg::parameter::object(
						ret
					)
				)
			)
		;
}

CGprogram
sge::cg::program::object::get() const
{
	return
		program_;
}

namespace
{

void
assert_program(
	sge::cg::context::object const &_context,
	CGprogram const _program,
	fcppt::string const _what
)
{
	SGE_CG_CHECK_STATE_LISTING(
		_context,
		_what,
		sge::cg::exception
	)

	FCPPT_ASSERT_ERROR(
		_program
		!=
		nullptr
	);
}

}
