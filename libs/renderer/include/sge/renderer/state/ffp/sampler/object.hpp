//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace sampler
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	object();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~object();
};

}
}
}
}
}

#endif
