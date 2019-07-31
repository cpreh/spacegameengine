//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CACHE_HPP_INCLUDED
#define SGE_PLUGIN_CACHE_HPP_INCLUDED

#include <sge/plugin/cache_fwd.hpp>
#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{

class cache
{
	FCPPT_NONCOPYABLE(
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
	typedef std::vector<
		sge::plugin::library::object_shared_ptr
	> plugin_container;

	plugin_container plugins_;
};

}
}

#endif
