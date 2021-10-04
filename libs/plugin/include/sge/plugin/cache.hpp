//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CACHE_HPP_INCLUDED
#define SGE_PLUGIN_CACHE_HPP_INCLUDED

#include <sge/plugin/cache_fwd.hpp>
#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::plugin
{

class cache
{
	FCPPT_NONMOVABLE(
		cache
	);
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	cache();

	SGE_PLUGIN_DETAIL_SYMBOL
	~cache();

	void
	add(
		sge::plugin::library::object_shared_ptr const &
	);
private:
	using
	plugin_container
	=
	std::vector<
		sge::plugin::library::object_shared_ptr
	>;

	plugin_container plugins_;
};

}

#endif
