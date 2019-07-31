//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_OCCLUSION_QUERY_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_HOLDER_HPP_INCLUDED

#include <sge/opengl/occlusion_query/config_fwd.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class holder
{
	FCPPT_NONCOPYABLE(
		holder
	);
public:
	explicit
	holder(
		sge::opengl::occlusion_query::config const &
	);

	~holder();

	sge::opengl::occlusion_query::id
	id() const;
private:
	sge::opengl::occlusion_query::config const &config_;

	sge::opengl::occlusion_query::id const id_;
};

}
}
}

#endif
