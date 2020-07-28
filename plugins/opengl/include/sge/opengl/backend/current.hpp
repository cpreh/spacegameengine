//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BACKEND_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace backend
{

class current
{
	FCPPT_NONMOVABLE(
		current
	);
protected:
	current();
public:
	virtual
	~current();

	[[nodiscard]]
	virtual
	sge::opengl::backend::fun_ptr
	load_function(
		std::string const &
	) const = 0;

	virtual
	void
	begin_rendering() = 0;

	virtual
	void
	end_rendering() = 0;

	virtual
	void
	vsync(
		sge::renderer::display_mode::vsync
	) = 0;
};

}
}
}

#endif
