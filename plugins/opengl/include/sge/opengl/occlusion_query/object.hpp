//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/opengl/occlusion_query/config_fwd.hpp>
#include <sge/opengl/occlusion_query/holder.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class object
:
	public sge::renderer::occlusion_query::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::occlusion_query::config const &
	);

	~object()
	override;
private:
	void
	begin()
	override;

	void
	end()
	override;

	sge::renderer::occlusion_query::optional_pixel_count
	result(
		sge::renderer::occlusion_query::blocking_wait block
	) const
	override;

	sge::opengl::occlusion_query::config const &config_;

	sge::opengl::occlusion_query::holder const holder_;
};

}
}
}

#endif
