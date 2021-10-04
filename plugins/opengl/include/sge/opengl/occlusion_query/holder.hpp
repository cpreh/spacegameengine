//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_OCCLUSION_QUERY_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_HOLDER_HPP_INCLUDED

#include <sge/opengl/occlusion_query/const_config_ref.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl::occlusion_query
{

class holder
{
	FCPPT_NONMOVABLE(
		holder
	);
public:
	explicit
	holder(
		sge::opengl::occlusion_query::const_config_ref
	);

	~holder();

	[[nodiscard]]
	sge::opengl::occlusion_query::id
	id() const;
private:
	sge::opengl::occlusion_query::const_config_ref const config_;

	sge::opengl::occlusion_query::id const id_;
};

}

#endif
