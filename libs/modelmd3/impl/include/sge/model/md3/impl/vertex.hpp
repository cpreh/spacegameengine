//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_VERTEX_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_VERTEX_HPP_INCLUDED

#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/impl/s16.hpp>
#include <sge/model/md3/impl/vertex_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

class vertex
{
public:
	vertex(
		std::istream &,
		sge::model::md3::load_flags_field
	);

	[[nodiscard]]
	sge::model::md3::impl::s16
	x() const;

	[[nodiscard]]
	sge::model::md3::impl::s16
	y() const;

	[[nodiscard]]
	sge::model::md3::impl::s16
	z() const;

	[[nodiscard]]
	sge::model::md3::impl::s16
	normal() const;
private:
	sge::model::md3::impl::s16 x_;

	sge::model::md3::impl::s16 y_;

	sge::model::md3::impl::s16 z_;

	sge::model::md3::impl::s16 normal_;
};

}
}
}
}

#endif
