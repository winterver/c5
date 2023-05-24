#pragma once
#include <vector>
#include "types.hpp"

// executable image for vm_t
class image
{
public:
	//void save_to_file();
	//static void load_from_file();
	
	// once these two are called, fill_*() should not be called,
	// or the two pointers will be invalidated.
	u8* get_text() { return text.data(); }
	u8* get_data() { return data.data(); }
	
	template<typename T, typename... Ts>
	void fill_text(T t, Ts... ts) { fill_text(t); fill_text(ts...); }
	template<typename T>
	void fill_text(T t) { add_text<T>(t); }

	template<typename T, typename... Ts>
	void fill_data(T t, Ts... ts) { fill_data(t); fill_data(ts...); }
	template<typename T>
	void fill_data(T t) { add_data<T>(t); }

private:
	template<typename T>
	void add_text(T t)
	{
		u8* b = (u8*)&t;
		for(int i = 0; i < sizeof(T); i++)
		{
			text.push_back(b[i]);
		}
	}
	template<typename T>
	void add_data(T t)
	{
		u8* b = (u8*)&t;
		for(int i = 0; i < sizeof(T); i++)
		{
			data.push_back(b[i]);
		}
	}

private:
	std::vector<u8> text;
	std::vector<u8> data;
};
