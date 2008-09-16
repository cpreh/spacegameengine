#include <sge/audio/loader/multi_loader.hpp>
#include <sge/audio/exception.hpp>
#include <sge/text.hpp>

sge::audio::multi_loader::multi_loader(plugin::manager &pm)
{
	for (plugin::iterator<loader> i = pm.begin<loader>(); i != pm.end<loader>(); ++i)
	{
		plugins.push_back(i->load());
		loaders.push_back(plugins.back()->get()());
	}
}	

sge::audio::file_ptr const sge::audio::multi_loader::load(path const &file)
{
	if (!boost::filesystem::exists(file))
		throw exception(SGE_TEXT("file \""+file.string()+"\" does not exist"));

	for (loader_container::iterator i = loaders.begin(); i != loaders.end(); ++i)
	{
		if (!(*i)->is_valid_file(file))
			continue;

		return (*i)->load(file);
	}

	throw exception(
		SGE_TEXT("couldn't find any audio loaders for file \""+file.string()+"\""));
	return file_ptr();
}
