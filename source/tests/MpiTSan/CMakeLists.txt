# find_package(LLVM REQUIRED CONFIG)

# list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

# include(AddLLVM)

# find_program(LLVM_LIT_PATH
#   NAME llvm-lit
#   HINTS ${LLVM_TOOLS_BINARY_DIR} 
#   PATHS ${LLVM_ROOT_DIR}/bin /usr/bin /usr/local/bin /opt/local/bin
#   DOC "llvm-lit executable. (Workaround for AddLLVM.cmake path not being set)"
# )
# if(LLVM_LIT_PATH)
#   set(LLVM_EXTERNAL_LIT ${LLVM_LIT_PATH})
# endif()

# find_program(LLVM_FILECHECK_PATH
#   NAME Filecheck
#   HINTS ${LLVM_TOOLS_BINARY_DIR} 
#   PATHS ${LLVM_ROOT_DIR}/bin /usr/bin /usr/local/bin /opt/local/bin
#   DOC "Filecheck executable. (Workaround for AddLLVM.cmake path not being set)"
# )
# if(LLVM_FILECHECK_PATH)
#   set(LLVM_EXTERNAL_FILECHECK ${LLVM_FILECHECK_PATH})
# endif()



# macro(pythonize_bool var)
#   if (${var})
#     set(${var} True)
#   else()
#     set(${var} False)
#   endif()
# endmacro()


# set(MUST_TEST_MPIC_COMPILER "mpicc" )
# set(MUST_TEST_COMPILER_FEATURES "")
# set(MUST_FILECHECK_EXECUTABLE "${LLVM_FILECHECK_PATH}")
# set(MUST_TEST_FLAGS "-rdynamic")
# set(MUST_MUSTRUN_EXECUTION_FLAGS "--must:mpiexec orterun --must:output stdout" )
# set(MUST_LIT_EXECUTABLE "${LLVM_LIT_PATH}")
# set(MUST_MUSTRUN "${CMAKE_INSTALL_PREFIX}/bin/mustrun")



# add_custom_target(check-mpitsan
#       COMMAND ${MUST_LIT_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}
#       COMMENT "Run MUST tests for MpiTSan-Checks"
# #       DEPENDS install
# )



# configure_file(lit.site.cfg.in lit.site.cfg @ONLY)
