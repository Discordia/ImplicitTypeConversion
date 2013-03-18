#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::wcout;
using std::endl;
using std::wstring;
using std::string;


class Value 
{
public:

	template<typename T>
    Value(const T value) {
      std::wostringstream wos;
      wos << value;
      v = wos.str();
    }

	template<>
	Value(const wstring& value) 
	{
		v = value;
	}

	template<>
    Value(const string& value) {
        v = wstring(value.begin(), value.end());
    }


	Value(Value& other)
	{
		this->v = other.v; 
	}

	template<typename T>
	operator T() const
	{
		T reply;
		std::wistringstream is;
		is.str(v);
		is >> reply;
		return reply;
	} 

	//operator const wstring&() const
	operator wstring() const
	{
		return v;
	}


private:
	wstring v;
};



class Config
{
public:
	virtual Value getValue(const string& key) const = 0;

	Value operator()(const string& key) 
	{
		return getValue(key);
	}
};

class ArgsConfig : public Config
{
	Value getValue(const string& key) const
	{
		return Value(L"test");
	}
};


int main()
{
	ArgsConfig config; 
	
	// This works:
	const wstring&& value = config("key");

	// But this do not
	// const wstring value2 = config("key");

	wcout << "Testing: " << value << endl;

	Value int_val(L"1");
    int i = int_val;

    cout << i + 1 << endl;

	return 0;
}