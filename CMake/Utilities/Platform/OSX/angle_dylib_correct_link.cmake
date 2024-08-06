# Define a function to modify library paths using install_name_tool
function(modify_dylib_paths target)
  # Use generator expressions to get the target file path
  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND install_name_tool -change ./libGLESv2.dylib @rpath/libGLESv2.dylib $<TARGET_FILE:${target}>
    COMMAND install_name_tool -change ./libEGL.dylib @rpath/libEGL.dylib $<TARGET_FILE:${target}>
    COMMENT "Modifying library paths for ${target} using install_name_tool"
  )
endfunction()
