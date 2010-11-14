#ifndef SGE_SHADER_SCOPED_HPP_INCLUDED
#define SGE_SHADER_SCOPED_HPP_INCLUDED

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
	explicit
	scoped(
		object &);

	~scoped();
private:
	object &object_;
};
}
}

#endif
