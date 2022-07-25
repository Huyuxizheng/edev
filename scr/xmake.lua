set_toolset("cc", "ccache arm-none-eabi-gcc")
set_toolset("cxx", "ccache arm-none-eabi-g++")
set_toolset("ld", "ccache arm-none-eabi-gcc")
set_languages("c99", "cxx11")

target("edev")
	set_kind("object")

	add_includedirs("./", {public = true})

    add_files("./**.c") --递归添加目录下的所有C文件


