#include <sge/bad_lexical_cast.hpp>
#include <sge/text.hpp>

sge::bad_lexical_cast::bad_lexical_cast(
	sge::type_info const &_source,
	sge::type_info const &_destination)
:
	exception(
		SGE_TEXT("Invalid lexical cast from type \"")+
		_source.name()+
		SGE_TEXT("\" to type \"")+
		_destination.name()+
		SGE_TEXT("\"")),
	source_(_source),
	destination_(_destination)
{
}

sge::type_info const &sge::bad_lexical_cast::source() const
{
	return source_;
}

sge::type_info const &sge::bad_lexical_cast::destination() const
{
	return destination_;
}
