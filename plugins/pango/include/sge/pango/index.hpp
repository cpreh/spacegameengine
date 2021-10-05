//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_INDEX_HPP_INCLUDED
#define SGE_PANGO_INDEX_HPP_INCLUDED

#include <sge/pango/index_fwd.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::pango
{

class index
{
public:
	FCPPT_DECLARE_STRONG_TYPEDEF(
		int,
		result_type
	);

	FCPPT_DECLARE_STRONG_TYPEDEF(
		int,
		trailing_type
	);

	index(
		result_type,
		trailing_type
	);

	[[nodiscard]]
	result_type
	result() const;

	[[nodiscard]]
	trailing_type
	trailing() const;
private:
	result_type result_;

	trailing_type trailing_;
};

}

#endif
