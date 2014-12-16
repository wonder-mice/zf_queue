if(NOT DEFINED CTAGS_EXECUTABLE)
	find_program(CTAGS_EXECUTABLE ctags)
endif()
if (CTAGS_EXECUTABLE)
	set(CTAGS_OPTS
		"--sort=foldcase"
		"--tag-relative"
		"--extra=+q"
		"--fields=+iaS"
		"--c-kinds=+px"
		"--c++-kinds=+px"
		"--exclude=CMakeLists.txt"
		"--exclude=CMakeFiles"
		"--exclude=Makefile"
		"--recurse"
		"--totals")
	set(CTAGS_OUTPUT_DIR ${CMAKE_SOURCE_DIR})
	set(CTAGS_OUTPUT "${CTAGS_OUTPUT_DIR}/tags")
	add_custom_target(tags
			COMMAND ${CTAGS_EXECUTABLE} ${CTAGS_OPTS}
			-f ${CTAGS_OUTPUT} "$<JOIN:$<TARGET_PROPERTY:tags,CTAGS_FILES>, >"
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	set_target_properties(tags PROPERTIES CTAGS_OUTPUT_DIR ${CTAGS_OUTPUT_DIR})
endif()

function(add_ctags_files)
	if (CTAGS_EXECUTABLE)
		get_target_property(CTAGS_OUTPUT_DIR tags CTAGS_OUTPUT_DIR)
		get_target_property(CTAGS_FILES tags CTAGS_FILES)
		if(NOT CTAGS_FILES)
			set(CTAGS_FILES "")
		endif()
		foreach(CTAGS_FILE ${ARGN})
			if(NOT IS_ABSOLUTE ${CTAGS_FILE})
				set(CTAGS_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${CTAGS_FILE})
			endif()
			file(RELATIVE_PATH CTAGS_FILE ${CTAGS_OUTPUT_DIR} ${CTAGS_FILE})
			set(CTAGS_FILES ${CTAGS_FILES} ${CTAGS_FILE})
		endforeach()
		set_target_properties(tags PROPERTIES CTAGS_FILES "${CTAGS_FILES}")
	endif()
endfunction()
