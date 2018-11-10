-- premake5.lua
workspace "platform"
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	location("build")
	warnings "Extra"

	filter { "platforms:*32" }
		architecture "x86"
	filter { "platforms:*64" }
		architecture "x64"
	filter { "toolset:msc*" }
		defines { "_ITERATOR_DEBUG_LEVEL=0", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS" }
		disablewarnings { "4200" } -- so we can use C99 flexible array syntax without a warning
	filter { "action:xcode* or toolset:clang*" }
		buildoptions { "-mlzcnt" }

project "canonical-test"
    kind "ConsoleApp"
    --language "C++"
    --cppdialect "C++17"
    language "C"
    cdialect "C11"
    includedirs { "include/canonical" }
    files { "test/canonical/*.c" }

project "diagnostic-test"
    kind "ConsoleApp"
    --language "C++"
    --cppdialect "C++17"
    language "C"
    cdialect "C11"
	includedirs { "include/diagnostic" }
    files { "test/diagnostic/*.c" }

project "posix-on-win32-test"
    kind "ConsoleApp"
    --language "C++"
    --cppdialect "C++17"
    language "C"
    cdialect "C11"
    includedirs { "posix-on-win32" }
    files { "test/posix/*.c" }

project "sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    files { "test/sandbox/*" }
