//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OCCLUSION_QUERY_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_OCCLUSION_QUERY_SCOPED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/occlusion_query/object_fwd.hpp>
#include <sge/renderer/occlusion_query/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace occlusion_query
{

class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	scoped(
		sge::renderer::occlusion_query::object &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::occlusion_query::object &
	get() const;
private:
	sge::renderer::occlusion_query::object &query_;
};

}
}
}

#endif
