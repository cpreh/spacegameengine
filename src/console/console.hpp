#ifndef SGE_CONSOLE_HPP_INCLUDED
#define SGE_CONSOLE_HPP_INCLUDED

// C++
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

// Boost
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include "../string.hpp"
#include "../exception.hpp"
#include "../iconv.hpp"

namespace sge
{
namespace con
{
	typedef sge::string                                string;
	typedef std::vector<string>                        arg_list;
	typedef boost::function<void (const arg_list &)>   function;

	class exception : public sge::exception
	{
	public:
		exception(const std::string &s);
	};

	class var_base
	{
	public:
		var_base(const string&);
		const string &name() const;
		virtual void set_string(const string &) = 0;
		virtual string get_string() const = 0;
		virtual ~var_base();
	private:
		string name_;
	};

	template<typename T>
	class var : public var_base
	{
	private:
		T value_;
	public:
		var(const string &name,const T &value_ = T()) : var_base(name),value_(value_) {}
		T &value() { return value_; }
		const T &value() const { return value_; }

		var<T> operator=(const T &r) { value_ = r; return *this; }

		void set_string(const string &n) 
		{
			try {
				value_ = boost::lexical_cast<T>(n);
			} catch (const boost::bad_lexical_cast &e) {
				throw exception("Couldn't convert string \"" + iconv(n) + "\" to console variable!");
			}
		}

		string get_string() const { return boost::lexical_cast<string>(value_); }
	};

	class singleton
	{
	public:
		typedef std::map<string,var_base *> var_container;
		typedef std::map<string,function> func_container;

		singleton();

		template<typename T>
		var<T> &get_var(const string &var_name)
		{
			if (vars_.find(var_name) == vars_.end())
				throw exception("A variable with name \"" + iconv(var_name) + "\" does not exist!");
			return *static_cast<var<T> *>(vars_[var_name]);
		}

		template<typename T>
		T &get_value(const string &var_name)
		{
			if (vars_.find(var_name) == vars_.end())
				throw exception("A variable with name \"" + iconv(var_name) + "\" does not exist!");
			return static_cast<var<T> *>(vars_[var_name])->value();
		}

		void add(const string &function_name,function fn);
		void add(const string &var_name,var_base &var);
		void remove(const string &var_name);

		var_container &vars();
		func_container &funcs();

		void read_config_file(const std::string &);

		string::value_type prefix() const;
		void prefix(string::value_type n);

		void eval(const string &);

		typedef boost::function<void (const string &)> chat_callback_type;

		void chat_callback(const chat_callback_type&);
	private:
		func_container funcs_;
		var_container  vars_;
		chat_callback_type chat_callback_;
		string::value_type prefix_;
	};

	singleton &instance();
}
}

#endif // CONSOLE_HPP
