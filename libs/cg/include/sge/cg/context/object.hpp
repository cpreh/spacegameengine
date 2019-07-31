//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_CG_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace context
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CG_DETAIL_SYMBOL
	object();

	SGE_CG_DETAIL_SYMBOL
	~object();

	SGE_CG_DETAIL_SYMBOL
	CGcontext
	get() const;
private:
	CGcontext const context_;
};

}
}
}

#endif
