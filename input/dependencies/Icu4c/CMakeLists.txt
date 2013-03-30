cmake_minimum_required(VERSION 2.8.10)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input")
	file(
		DOWNLOAD "http://download.icu-project.org/files/icu4c/51.1/icu4c-51_1-src.tgz" "${CMAKE_CURRENT_SOURCE_DIR}/input.tgz"
		SHOW_PROGRESS
		EXPECTED_MD5 "6eef33b229d0239d654983028c9c7053"
	)

	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E tar xvzf input.tgz
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)

	file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/icu" "${CMAKE_CURRENT_SOURCE_DIR}/input")

	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/input.tgz")
endif()
