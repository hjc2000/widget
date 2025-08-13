add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})
target_import_base(${ProjectName} PUBLIC)
target_import_qt_widgets(${ProjectName} PUBLIC)
target_import_qt_opengl(${ProjectName} PUBLIC)
target_import_qwt(${ProjectName} PUBLIC)
target_import_qxlsx(${ProjectName} PUBLIC)
target_import_qt_serial_port(${ProjectName} PUBLIC)



# 添加测试程序
if(("${platform}" STREQUAL "msys") OR
   ("${platform}" STREQUAL "msys-clang"))
	set(test_exe_target_name "test")

	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		# set(exe_type "WIN32")
		set(exe_type "")
	else()
		set(exe_type "")
	endif()

	add_executable(${test_exe_target_name} ${exe_type})
	target_import_test(${test_exe_target_name})

	target_link_options(${test_exe_target_name} PUBLIC -Wl,--start-group)
	target_link_libraries(${test_exe_target_name} PUBLIC ${ProjectName})
	target_link_options(${test_exe_target_name} PUBLIC -Wl,--end-group)
endif()
