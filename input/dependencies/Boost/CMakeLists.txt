cmake_minimum_required(VERSION 2.8.7)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input")
	if(WIN32)
		set(Extension zip)
		set(Md5 "c618e030fd4882e4dbacf54baf824544")
	else()
		set(Extension tar.gz)
		set(Md5 "57a9e2047c0f511c4dfcf00eb5eb2fbb")
	endif()
	file(
		DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.${Extension}/download" "${CMAKE_CURRENT_SOURCE_DIR}/input.${Extension}"
		SHOW_PROGRESS
		EXPECTED_MD5 ${Md5}
	)
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf input.${Extension}
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)
	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/input.${Extension}")
	file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/boost_1_53_0" "${CMAKE_CURRENT_SOURCE_DIR}/input")
endif()
