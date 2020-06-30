# CMake for Lua
file(GLOB LUA_C_SRC *.h *.c)

# Remove onalua.c and lua.c
list(FILTER LUA_C_SRC EXCLUDE REGEX ".*onelua.c$")
list(FILTER LUA_C_SRC EXCLUDE REGEX ".*lua.c$")

# Export.
set(LUA_SRCS
	${LUA_C_SRC}
	CACHE
	FILEPATH
	"Lua C source files")

# Export Lua include path
set(LUA_INCLUDE
	${CMAKE_CURRENT_SOURCE_DIR}
	CACHE
	FILEPATH
	"Lua include directory")