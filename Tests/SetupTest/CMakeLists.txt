set(SRC
	"main.cpp"
	"DefaultShader.vert"
	"DefaultShader.frag"
)

add_executable("SetupTest" "${SRC}")
target_include_directories("SetupTest" PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries("SetupTest" PRIVATE "Ion")

SetOutputDirectory("SetupTest" "")
SetWorkingDirectoryPlane("SetupTest" "${CMAKE_SOURCE_DIR}/Tests/SetupTest")