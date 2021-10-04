//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_SHADER_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_SHADER_HPP_INCLUDED

#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/s32.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge::model::md3::impl
{

class shader
{
public:
	explicit
	shader(
		std::istream &
	);

	[[nodiscard]]
	sge::model::md3::string const &
	name() const;

	[[nodiscard]]
	sge::model::md3::impl::s32
	shader_index() const;
private:
	sge::model::md3::string name_;

	sge::model::md3::impl::s32 shader_index_;
};

}

#endif
