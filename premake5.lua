workspace "CellularAutomata"
		architecture "x64"
		startproject "CellularAutomata"

		configurations
		{
			"Debug",
			"Release"
		}

		flags
		{
			"MultiProcessorCompile"
		}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "XYZEngine/Dependencies"
IncludeDir["GLFW"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/glfw/include"
IncludeDir["GLEW"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/GLEW/include"
IncludeDir["glm"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/glm"
IncludeDir["OpenAL"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/OpenAL-Soft"
IncludeDir["MiniMp3"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/minimp3"
IncludeDir["FreeType"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/freetype-2.10.1"
IncludeDir["Asio"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/asio/include"
IncludeDir["Lua"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/lua/include"
IncludeDir["Sol"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/sol2/include"
IncludeDir["mono"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/mono/include"
IncludeDir["TrianglePP"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/TrianglePP/source"
IncludeDir["yaml"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/yaml-cpp/include"
IncludeDir["ImGui"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/imgui"
IncludeDir["ImGuizmo"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/ImGuizmo"
IncludeDir["box2d"] = "%{wks.location}/XYZEngine/XYZEngine/vendor/box2d/include"


include "XYZEngine/Projects"
include "CellularAutomata"