
target("edev")

	set_kind("object")

	add_includedirs("./", {public = true})

    add_files("./**.c") --递归添加目录下的所有C文件


