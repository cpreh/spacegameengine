//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_TEXPOS_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_TEXPOS_HPP_INCLUDED

#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/texcoord.hpp>
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

class texpos
{
public:
	explicit
	texpos(
		std::istream &
	);

	[[nodiscard]]
	sge::model::md3::texcoord
	texcoord() const;
private:
	sge::model::md3::scalar x_;
	sge::model::md3::scalar y_;
};

}
}
}
}

#endif
