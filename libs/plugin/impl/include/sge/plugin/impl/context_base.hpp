//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_CONTEXT_BASE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_CONTEXT_BASE_HPP_INCLUDED

#include <sge/plugin/context_base_fwd.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/weak_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{

class context_base
{
	FCPPT_NONCOPYABLE(
		context_base
	);
public:
	context_base(
		sge::plugin::optional_cache_ref const &,
		std::filesystem::path const &
	);

	~context_base();

	SGE_PLUGIN_DETAIL_SYMBOL
	std::filesystem::path const &
	path() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::info const &
	info() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::library::object_shared_ptr
	load();
private:
	sge::plugin::optional_cache_ref const cache_;

	std::filesystem::path const path_;

	sge::plugin::info const info_;

	typedef
	fcppt::weak_ptr<
		sge::plugin::library::object
	>
	library_weak_ptr;

	library_weak_ptr library_ptr_;
};

}
}

#endif
