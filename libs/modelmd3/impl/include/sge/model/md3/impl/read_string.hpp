//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_READ_STRING_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_READ_STRING_HPP_INCLUDED

#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/max_qpath.hpp>
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

template<
	sge::model::md3::string::size_type Max
>
sge::model::md3::string
read_string(
	std::istream &
);

}
}
}
}

#define SGE_MODEL_MD3_IMPL_DECLARE_READ_STRING(\
	maxc\
)\
extern \
template \
sge::model::md3::string \
sge::model::md3::impl::read_string< \
	maxc\
>( \
	std::istream &\
)

SGE_MODEL_MD3_IMPL_DECLARE_READ_STRING(
	sge::model::md3::impl::max_qpath::value
);

SGE_MODEL_MD3_IMPL_DECLARE_READ_STRING(
	16
);

#endif
