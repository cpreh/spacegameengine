//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_TAG_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_TAG_HPP_INCLUDED

#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/axis_array.hpp>
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

class tag
{
public:
	explicit
	tag(
		std::istream &
	);

	[[nodiscard]]
	sge::model::md3::string const &
	name() const;

	[[nodiscard]]
	sge::model::md3::impl::vec3 const &
	origin() const;

	[[nodiscard]]
	sge::model::md3::impl::axis_array const &
	axis() const;
private:
	sge::model::md3::string name_;

	sge::model::md3::impl::vec3 origin_;

	sge::model::md3::impl::axis_array axis_;
};

}
}
}
}

#endif
