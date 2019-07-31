//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LIBRARY_OBJECT_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_OBJECT_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <sge/plugin/impl/library/loaded_symbol.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#endif


namespace sge
{
namespace plugin
{
namespace library
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	explicit
	object(
		boost::filesystem::path const &
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	~object();

	sge::plugin::impl::library::loaded_symbol
	load(
		sge::plugin::library::symbol_string const &
	);

	boost::filesystem::path const &
	name() const;
private:
	boost::filesystem::path const name_;

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	HMODULE const handle_;

	struct destroyer;

	fcppt::unique_ptr<
		destroyer
	> const destroyer_;
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	void *const handle_;
#else
#error "Don't know how to implement plugin::library!"
#endif
};

}
}
}

#endif
