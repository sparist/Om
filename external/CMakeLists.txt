cmake_minimum_required(VERSION 2.8.10)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input/Icu4c")
	file(
		DOWNLOAD "http://download.icu-project.org/files/icu4c/51.1/icu4c-51_1-src.tgz" "${CMAKE_CURRENT_SOURCE_DIR}/input/Icu4c.tgz"
		SHOW_PROGRESS
		EXPECTED_MD5 "6eef33b229d0239d654983028c9c7053"
	)
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf Icu4c.tgz
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input"
	)
	file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/input/icu" "${CMAKE_CURRENT_SOURCE_DIR}/input/Icu4c")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input/Boost")
	if(MSVC)
		file(
			DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.zip/download" "${CMAKE_CURRENT_SOURCE_DIR}/input/Boost.zip"
			SHOW_PROGRESS
			EXPECTED_MD5 "c618e030fd4882e4dbacf54baf824544"
		)
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E tar xvzf Boost.zip
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input"
		)
	else()
		file(
			DOWNLOAD "http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.tar.gz/download" "${CMAKE_CURRENT_SOURCE_DIR}/input/Boost.tar.gz"
			SHOW_PROGRESS
			EXPECTED_MD5 "57a9e2047c0f511c4dfcf00eb5eb2fbb"
		)
		execute_process(
			COMMAND "${CMAKE_COMMAND}" -E tar xvzf Boost.tar.gz
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/input"
		)
	endif()
	file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/input/boost_1_53_0" "${CMAKE_CURRENT_SOURCE_DIR}/input/Boost")
endif()
