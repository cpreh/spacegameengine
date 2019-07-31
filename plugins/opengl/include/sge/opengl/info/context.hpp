//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/version.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace info
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		fcppt::log::object &,
		sge::opengl::backend::current const &
	);

	~context();

	sge::opengl::info::version
	version() const;

	sge::opengl::info::extension_set const &
	extensions() const;

	sge::opengl::backend::fun_ptr
	load_function(
		std::string const &
	) const;
private:
	sge::opengl::backend::current const &current_;

	sge::opengl::info::version const version_;

	sge::opengl::info::extension_set const extensions_;
};

}
}
}

#endif
