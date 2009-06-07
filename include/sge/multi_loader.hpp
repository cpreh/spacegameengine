#ifndef SGE_MULTI_LOADER_HPP_INCLUDED
#define SGE_MULTI_LOADER_HPP_INCLUDED

#include <sge/noncopyable.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/context.hpp>
#include <sge/filesystem/path.hpp>
#include <vector>

namespace sge
{
template<
	typename Loader,
	typename File,
	typename Exception>
class multi_loader
{
SGE_NONCOPYABLE(multi_loader)
public:
	typedef Loader loader;
	typedef File file;
	typedef shared_ptr<loader> loader_ptr;
	typedef shared_ptr<file> file_ptr;
	typedef Exception exception;

	explicit multi_loader(
		plugin::manager &);

	file_ptr const
	load(
		filesystem::path const &);
private:
	typedef std::vector<
		typename plugin::context<
			loader
		>::ptr_type
	> plugin_container;

	typedef std::vector<
		loader_ptr
	> loader_container;

	plugin_container plugins;
	loader_container loaders;
};
}

#include "detail/multi_loader_impl.hpp"

#endif
