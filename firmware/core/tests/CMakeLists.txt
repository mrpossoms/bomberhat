set(CORE_TESTS
	kalman-filter.cpp
)

add_executable (core-tests ${CORE_TESTS})

foreach (test ${CORE_TESTS})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND ${TName})

 # include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
 target_link_libraries(core-tests bh.core)
endforeach ()