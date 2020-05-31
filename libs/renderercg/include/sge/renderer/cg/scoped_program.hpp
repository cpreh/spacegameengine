//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CG_SCOPED_PROGRAM_HPP_INCLUDED
#define SGE_RENDERER_CG_SCOPED_PROGRAM_HPP_INCLUDED

#include <sge/renderer/cg/const_loaded_program_ref.hpp>
#include <sge/renderer/cg/scoped_program_fwd.hpp>
#include <sge/renderer/cg/detail/symbol.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace cg
{

class scoped_program
{
	FCPPT_NONMOVABLE(
		scoped_program
	);
public:
	SGE_RENDERER_CG_DETAIL_SYMBOL
	scoped_program(
		sge::renderer::context::core_ref,
		sge::renderer::cg::const_loaded_program_ref
	);

	SGE_RENDERER_CG_DETAIL_SYMBOL
	~scoped_program();
private:
	sge::renderer::context::core_ref const context_;

	sge::renderer::cg::const_loaded_program_ref const program_;
};

}
}
}

#endif
