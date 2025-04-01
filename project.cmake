# 编译为动态库
add_library(${ProjectName})
target_import_src(${ProjectName})
target_import_base(${ProjectName} PUBLIC)
target_import_qt_widgets(${ProjectName} PUBLIC)
target_import_qt_opengl(${ProjectName} PUBLIC)
target_import_qwt(${ProjectName} PUBLIC)
target_import_qxlsx(${ProjectName} PUBLIC)

# 添加测试程序
if(1)
	set(exe_name "test")

	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(exe_type "WIN32")
	else()
		set(exe_type "")
	endif()

	add_executable(${exe_name} ${exe_type} ${CMAKE_CURRENT_SOURCE_DIR}/exe/main.cpp)

	target_link_libraries(${ProjectName} PUBLIC -Wl,--start-group)
	target_link_libraries(${exe_name} PUBLIC ${ProjectName})
	target_link_libraries(${ProjectName} PUBLIC -Wl,--end-group)

	target_install(${exe_name})
endif()
