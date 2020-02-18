//Config.h  
#pragma once  

#ifndef UTILS_CONFIG_H
#define UTILS_CONFIG_H
#include <string>  
#include <map>  
#include <iostream>  
#include <fstream>  
#include <sstream>  

using namespace std;

/*
* \brief Generic configuration Class
*
*/
class Config {
	// Data  
public:
	std::string m_Delimiter;  //!< separator between key and value  
	std::string m_Comment;    //!< separator between value and comments  
	std::map<std::string, std::string> m_Contents;  //!< extracted keys and values

	typedef std::map<std::string, std::string>::iterator mapi;
	typedef std::map<std::string, std::string>::const_iterator mapci;
	// Methods  
public:

	Config(std::string filename, std::string delimiter = "=", std::string comment = "#");
	Config();
	template<class T> T Read(const std::string& in_key) const;  //!<Search for key and read value or optional default value, call as read<T>  
	template<class T> T Read(const std::string& in_key, const T& in_value) const;
	template<class T> bool ReadInto(T& out_var, const std::string& in_key) const;
	template<class T>
	bool ReadInto(T& out_var, const std::string& in_key, const T& in_value) const;
	bool FileExist(std::string filename);
    bool ReadFile(std::string filename, std::string delimiter = "=", std::string comment = "#");

	// Check whether key exists in configuration  
	bool KeyExists(const std::string& in_key) const;

	// Modify keys and values  
	template<class T> void Add(const std::string& in_key, const T& in_value);
	void Remove(const std::string& in_key);

	// Check or change configuration syntax  
	std::string GetDelimiter() const { return m_Delimiter; }
	std::string GetComment() const { return m_Comment; }
	std::string SetDelimiter(const std::string& in_s)
	{
		std::string old = m_Delimiter;  m_Delimiter = in_s;  return old;
	}
	std::string SetComment(const std::string& in_s)
	{
		std::string old = m_Comment;  m_Comment = in_s;  return old;
	}

	// Write or read configuration  
	friend std::ostream& operator<<(std::ostream& os, const Config& cf);
	friend std::istream& operator>>(std::istream& is, Config& cf);

public:
	template<class T> static std::string T_as_string(const T& t);
	template<class T> static T string_as_T(const std::string& s);
	static void Trim(std::string& inout_s);


	// Exception types  
public:

	struct Key_not_found {  // thrown only by T read(key) variant of read()  
		std::string key;
		Key_not_found(const std::string& key_ = std::string())
			: key(key_) {}
	};
};

#endif //UTILS_CONFIG_H