/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
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

class SGE_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_RENDERER_SYMBOL
	object();
public:
	SGE_RENDERER_SYMBOL
	virtual
	~object() = 0;

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
	sge::renderer::occlusion_query::optional_pixel_count const
	result(
		sge::renderer::occlusion_query::blocking_wait block
	) const = 0;
};

}
}
}

#endif
