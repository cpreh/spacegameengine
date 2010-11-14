#ifndef SGE_SHADER_SCOPED_HPP_INCLUDED
#define SGE_SHADER_SCOPED_HPP_INCLUDED

#include <sge/shader/symbol.hpp>
#include <sge/shader/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace shader
{
class scoped
{
FCPPT_NONCOPYABLE(scoped)
public:
	SGE_SHADER_SYMBOL explicit
	scoped(
		object &);

	SGE_SHADER_SYMBOL ~scoped();
private:
	object &object_;
};
}
}

#endif
