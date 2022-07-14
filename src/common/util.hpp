/**
 * Some utils - mainly for portability
 */
#pragma once

#include <cstring>
#include <fstream>
#include <string>
#include <memory>

#include "strtools.hpp"

/** === Portability aids === **/

#define _stricmp dont_use__stricmp
#define stricmp dont_use_stricmp

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

/******************************/
namespace util {

	/**
	 * Helper to quickly read a file off disk
	 */
	static std::size_t read_file(const std::string& path, std::uint8_t*& outPtr) {
		std::ifstream stream(path, std::ios::in | std::ios::binary);
		outPtr = nullptr;
		if (!stream.good())
			return 0;

		stream.seekg(0, std::ios::end);
		auto size = stream.tellg();
		stream.seekg(0, std::ios::beg);
		
		if (!size)
			return 0;
		
		outPtr = new std::uint8_t[size];
		stream.read((char*)outPtr, size);
		
		return size;
	}

	/**
	 * RAII cleanup object
	 */
	template<class T>
	class cleanup {
	public:
		[[nodiscard]] cleanup(const T& obj) :
			m_func(obj) {}
		cleanup(const cleanup&) = delete;
		~cleanup() {m_func();}
	private:
		T m_func;
	};
}
