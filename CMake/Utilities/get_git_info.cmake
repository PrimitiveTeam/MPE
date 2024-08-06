cmake_minimum_required(VERSION 3.22)

function(get_git_info)
    # Get the current branch name
    execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Get the current commit hash - full
    execute_process(
        COMMAND git rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH_FULL
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Get the current commit hash - short
    execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH_SHORT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(GIT_BRANCH ${GIT_BRANCH} PARENT_SCOPE)
    set(GIT_COMMIT_HASH ${GIT_COMMIT_HASH_FULL} PARENT_SCOPE)
    set(GIT_COMMIT_HASH_SHORT ${GIT_COMMIT_HASH_SHORT} PARENT_SCOPE)
endfunction()

get_git_info()

message(STATUS "Current Git branch: ${GIT_BRANCH}")
message(STATUS "Current Git commit hash: ${GIT_COMMIT_HASH}")
message(STATUS "Current Git commit hash (short): ${GIT_COMMIT_HASH_SHORT}")
