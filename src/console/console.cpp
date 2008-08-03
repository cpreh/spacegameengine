#include <sge/string.hpp>
#include <sge/path.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/console/console.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/var_base.hpp>
#include <sge/console/singleton.hpp>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <locale>
#include <ostream>

void sge::con::eval(const string &s)
{
	instance().eval(s);
}

void sge::con::chat_callback(const callback &c)
{
	instance().chat = c;
}

void sge::con::add(const string &name,const callback &c)
{
	instance().add(name,c);
}

void sge::con::prefix(const string::value_type &c)
{
	instance().prefix = c;
}

sge::string::value_type sge::con::prefix()
{
	return instance().prefix;
}

void sge::con::read_config(const path &s)
{
	instance().read_config(s);
}

const sge::con::var_map &sge::con::vars()
{
	return instance().vars;
}

const sge::con::callback_map &sge::con::funcs()
{
	return instance().funcs;
}

sge::string sge::con::get_var(const sge::string &name)
{
	return instance().get_var(name);
}

void sge::con::set_var(const sge::string &name,const sge::string &value)
{
	instance().set_var(name,value);
}

void sge::con::latch(const sge::string &name,const sge::string &value)
{
	instance().latch(name,value);
}
