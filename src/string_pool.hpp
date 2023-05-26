#pragma once
#include <vector>

class string_pool {
private:
	string_pool() { }
	string_pool(string_pool& s) = delete;
	string_pool(string_pool&& s) = delete;
	void operator=(string_pool& s) = delete;

public:
	static string_pool& get_instance()
	{
		static string_pool instance;
		return instance;
	}

	char* add(const char* s)
	{
		for(auto x : strs)
		{
			if (!strcmp(x, s))
			{
				return x;
			}
		}
		strs.push_back(strdup(s));
		return strs.back();
	}
private:
	std::vector<char*> strs;
};
