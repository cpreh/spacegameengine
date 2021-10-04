//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_TRIANGLE_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_TRIANGLE_HPP_INCLUDED

#include <sge/model/md3/impl/index_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge::model::md3::impl
{

class triangle
{
public:
	explicit
	triangle(
		std::istream &
	);

	[[nodiscard]]
	sge::model::md3::impl::index_array const &
	indices() const;
private:
	sge::model::md3::impl::index_array indices_;
};

}

#endif
