//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object_fwd.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace occlusion_query
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

	/**
	\brief Begins the query

	Every pixel that passes the depth test starting from here on
	will increase the result value by one.
	*/
	virtual
	void
	begin() = 0;

	/**
	\brief Stops the query

	The result can then be obtained using the <code>result()</code>
	function.
	*/
	virtual
	void
	end() = 0;

	/**
	\brief Returns the result of the query, if available

	After a call to <code>end()</code> the result can be obtained using
	this function. \a block specifies if the implementation should block
	while waiting for the result. If \a block is false and the result is
	not available, then the function returns an empty optional. Note, that
	even with \a block set to true, the return value can still be empty. In
	such a case, the issued query must be restarted.

	\param block Whether the wait should block

	\return The number of pixels that passed the depth test or an empty
	optional if the result could not be obtained
	*/
	virtual
	sge::renderer::occlusion_query::optional_pixel_count
	result(
		sge::renderer::occlusion_query::blocking_wait block
	) const = 0;
};

}
}
}

#endif
