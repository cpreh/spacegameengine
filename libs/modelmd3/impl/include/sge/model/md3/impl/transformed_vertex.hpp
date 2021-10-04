//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_TRANSFORMED_VERTEX_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_TRANSFORMED_VERTEX_HPP_INCLUDED

#include <sge/model/md3/impl/vec3.hpp>
#include <sge/model/md3/impl/vertex_fwd.hpp>


namespace sge::model::md3::impl
{

class transformed_vertex
{
public:
	explicit
	transformed_vertex(
		sge::model::md3::impl::vertex const &
	);

	[[nodiscard]]
	sge::model::md3::impl::vec3 const &
	pos() const;

	[[nodiscard]]
	sge::model::md3::impl::vec3 const &
	normal() const;
private:
	sge::model::md3::impl::vec3 pos_;

	sge::model::md3::impl::vec3 normal_;
};

}

#endif
