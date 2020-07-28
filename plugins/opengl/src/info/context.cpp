//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/const_current_ref.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/get_extensions.hpp>
#include <sge/opengl/info/get_version.hpp>
#include <sge/opengl/info/version.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


#undef major
#undef minor

sge::opengl::info::context::context(
	fcppt::log::object &_log,
	sge::opengl::backend::const_current_ref const _current
)
:
	current_(
		_current
	),
	version_(
		sge::opengl::info::get_version(
			_current.get()
		)
	),
	extensions_(
		sge::opengl::info::get_extensions(
			_current.get()
		)
	)
{
	FCPPT_LOG_INFO(
		_log,
		fcppt::log::out
			<< FCPPT_TEXT("Version is: ")
			<< version_.major()
			<< FCPPT_TEXT('.')
			<< version_.minor()
	)
}

sge::opengl::info::context::~context()
= default;

sge::opengl::info::version
sge::opengl::info::context::version() const
{
	return
		version_;
}

sge::opengl::info::extension_set const &
sge::opengl::info::context::extensions() const
{
	return
		extensions_;
}

sge::opengl::backend::fun_ptr
sge::opengl::info::context::load_function(
	std::string const &_name
) const
{
	return
		current_.get().load_function(
			_name
		);
}
