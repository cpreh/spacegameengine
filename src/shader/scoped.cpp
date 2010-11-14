#include <sge/shader/scoped.hpp>
#include <sge/shader/object.hpp>

sge::shader::scoped::scoped(
	object &_object)
:
	object_(
		_object)
{
	object_.activate();
}

sge::shader::scoped::~scoped()
{
	object_.deactivate();
}
