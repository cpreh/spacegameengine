//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_FRAME_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_FRAME_HPP_INCLUDED

#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

class frame
{
public:
	explicit
	frame(
		std::istream &
	);

	sge::model::md3::impl::vec3 const &
	min_bounds() const;

	sge::model::md3::impl::vec3 const &
	max_bounds() const;

	sge::model::md3::impl::vec3 const &
	local_origin() const;

	sge::model::md3::scalar
	radius() const;

	sge::model::md3::string const &
	name() const;
private:
	sge::model::md3::impl::vec3
		min_bounds_,
		max_bounds_,
		local_origin_;

	sge::model::md3::scalar radius_;

	sge::model::md3::string name_;
};

}
}
}
}

#endif
