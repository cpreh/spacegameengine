#ifndef SGE_BAD_LEXICAL_CAST_HPP_INCLUDED
#define SGE_BAD_LEXICAL_CAST_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/type_info.hpp>

namespace sge
{
class bad_lexical_cast : public exception
{
public:
	SGE_SYMBOL explicit bad_lexical_cast(
		type_info const &source,
		type_info const &dest);
	
	type_info const &source() const;
	type_info const &destination() const;
private:
	type_info const source_,destination_;
};
}

#endif
