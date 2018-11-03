#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace DecentEngine {

class Logger{
	std::string m_class;
	std::fstream m_file;
public:
	enum class Type {DEBUG, INFO, WARN, ERROR};

	Logger(const std::string& className) : m_class(className) 
	{
		time_t rawTime;
		struct tm * timeinfo;
		char buffer[128];

		time(&rawTime);
		timeinfo = localtime(&rawTime);

		strftime(buffer, sizeof(buffer), "logs/%Y-%m-%d : %H.log", timeinfo);
		std::string logdir(buffer);

		m_file.open(logdir, std::fstream::app);
	}


	~Logger(){
		if(m_file.is_open()){
			m_file.close();
		}
	}

	template <typename T, typename... TArgs>
	void log(Type type, T first, TArgs... args){
		time_t rawTime;
		struct tm * timeinfo;
		char buffer[128];

		time(&rawTime);
		timeinfo = localtime(&rawTime);

		strftime(buffer, sizeof(buffer), " %H:%M:%S", timeinfo);
		std::string currtime(buffer);

		std::stringstream sstr;

		m_file << currtime << " : [" << m_class << ']' << " - (" << getTypeStr(type) << "): " << first;
		std::cout << currtime << " : [" << m_class << ']' << " - (" << getTypeStr(type) << "): " << first;
	
		logObj(args...);
		
		m_file << '\n';
		std::cout << '\n';
	}

	template <typename T, typename... TArgs>
	void logObj(T t, TArgs... args){
		std::cout << t << " ";
		m_file << t << " ";

		logObj(args...);
	}

	template <typename T>
	void logObj(T t){
		std::cout << t << " ";
		m_file << t << " ";
	}

	static std::string getTypeStr(Type type) {
		if(type == Type::DEBUG) return "DEBUG";
		if(type == Type::INFO) return "INFO";
		if(type == Type::WARN) return "WARN";
		if(type == Type::ERROR) return "ERROR";
		return "UNKNOWN";
	}
};

}

#endif
