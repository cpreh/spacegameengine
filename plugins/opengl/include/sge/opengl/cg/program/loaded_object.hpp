//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace cg
{
namespace program
{

class loaded_object
:
	public sge::renderer::cg::loaded_program
{
	FCPPT_NONCOPYABLE(
		loaded_object
	);
public:
	explicit
	loaded_object(
		sge::cg::program::object &
	);

	~loaded_object()
	override;

	void
	activate() const;

	void
	deactivate() const;
private:
	sge::cg::program::object &program_;
};

}
}
}
}

#endif
