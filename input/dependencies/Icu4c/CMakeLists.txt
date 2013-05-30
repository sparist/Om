cmake_minimum_required(VERSION 2.8.7)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input")
	file(
		DOWNLOAD "http://download.icu-project.org/files/icu4c/51.2/icu4c-51_2-src.tgz" "${CMAKE_CURRENT_SOURCE_DIR}/input.tgz"
		SHOW_PROGRESS
		EXPECTED_MD5 "072e501b87065f3a0ca888f1b5165709"
	)

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf input.tgz
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)

	file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/icu" "${CMAKE_CURRENT_SOURCE_DIR}/input")

	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/input.tgz")
endif()
