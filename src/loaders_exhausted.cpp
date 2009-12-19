#include <sge/loaders_exhausted.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>

sge::loaders_exhausted::loaders_exhausted(
	filesystem::path const &p)
:
	exception(FCPPT_TEXT("exhausted all loaders for file \"")+p.string()+FCPPT_TEXT("\""))
{

}
