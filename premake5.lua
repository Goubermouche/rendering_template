workspace "workspace"
    location "."
    configurations { "Debug", "Release" }
    platforms { "x64" }

    filter { "platforms:x64" }
        system "Windows"
        architecture "x64"

    filter { }

project "project"
    kind "ConsoleApp"
    language "C++"
    location "."
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}" 
    
    files { 
        "./src/**.h", 
        "./src/**.cpp",
        "./dep/glad/src/glad.c",
        "./dep/imgui/*.cpp",
        "./dep/imgui/backends/imgui_impl_glfw.cpp",
        "./dep/imgui/backends/imgui_impl_opengl3.cpp"
    } 

    includedirs {
        "./dep/glfw/include",
        "./dep/glad/include",
        "./dep/imgui",
        "./dep/imgui/backends"
    }

    links {
        "opengl32",
        "glfw3"
    }

    filter "architecture:x64"
        libdirs { 
            "./dep/glfw/x64/lib",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter {}