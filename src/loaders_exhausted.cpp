#include <sge/loaders_exhausted.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>

sge::loaders_exhausted::loaders_exhausted(
	filesystem::path const &p)
:
	exception(SGE_TEXT("exhausted all loaders for file \"")+p.string()+SGE_TEXT("\""))
{

}
