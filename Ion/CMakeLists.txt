set(SRC
	"Ipch.h"
	"IBase.h"

	# --------------------------------
	# Tokenization
	"Tokenization/ITokenizer.h"
	"Tokenization/ITokenizer.cpp"
	"Tokenization/ITokens.h"
	"Tokenization/ITokens.cpp"
)

set(PRIVATE_INC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

set(PUBLIC_LIB
    ""
)

set(PRIVATE_LIB
    ""
)


# ------------------------------------------------------------------
# Setup
add_library("Ion" SHARED "${SRC}")
target_include_directories("Ion"
	PUBLIC
		"${PUBLIC_INC}"
	PRIVATE
		"${PRIVATE_INC}"
)
target_link_libraries("Ion"
	PUBLIC
		"${PUBLIC_LIB}"
	PRIVATE
		"${PRIVATE_LIB}"
)
target_compile_definitions("Ion" PRIVATE "ION_BUILD")
target_precompile_headers("Ion" PRIVATE "Ipch.h")

AddRecursiveFilters("${SRC}")
SetOutputDirectory("Ion" "")
SetWorkingDirectoryPlane("Ion" "${CMAKE_SOURCE_DIR}")
