//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CG_LOADED_PROGRAM_HPP_INCLUDED
#define SGE_RENDERER_CG_LOADED_PROGRAM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace cg
{

class SGE_CORE_DETAIL_CLASS_SYMBOL loaded_program
{
	FCPPT_NONMOVABLE(
		loaded_program
	);
protected:
	SGE_RENDERER_CG_DETAIL_SYMBOL
	loaded_program();
public:
	SGE_RENDERER_CG_DETAIL_SYMBOL
	virtual
	~loaded_program();
};

}
}
}

#endif
