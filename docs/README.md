## 加入到工程
### 关于编译器
edev中使用了GNU和微软的C语言拓展语法，GUN GCC编译器编译时需要使用`-fms-extensions`选项启用微软C语言拓展语法。

MDK环境中需要勾选GNU拓展语法。

### 使用xmake集成
edev项目使用xmake编译工程，首先在工程中引入edev的xmake配置，之后在目标中添加依赖即可把edev集成到项目中
```lua
--GNU编译器需要启用微软C语言拓展语法
add_cflags("-fms-extensions")

--引入edev xmake配置文件
includes("./edev/scr/edev.lua")

target(test)
    --为需要的目标添加edev依赖
	add_deps("edev")

```

### 使用MDK集成







