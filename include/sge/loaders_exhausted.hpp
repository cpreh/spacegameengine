#ifndef SGE_LOADERS_EXHAUSTED_HPP_INCLUDED
#define SGE_LOADERS_EXHAUSTED_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/export.hpp>
#include <sge/filesystem/path.hpp>

namespace sge
{
class SGE_CLASS_SYMBOL loaders_exhausted
:
	public exception
{
public:
	SGE_SYMBOL loaders_exhausted(
		filesystem::path const &);
};
}

#endif
