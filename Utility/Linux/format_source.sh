#!/bin/bash

# Enable debugging
set -x

# Get the script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Path to clang-format executable
CLANG_FORMAT=clang-format

# Path to the .clang-format file
CLANG_FORMAT_FILE="$SCRIPT_DIR/../.clang-format"

# Path to the file containing directory paths
DIR_LIST="$SCRIPT_DIR/../.dirs_to_format"

# Read each line in .dirs_to_format, prepend ../../, and format files in those directories
while IFS= read -r DIR; do
    DIR_PATH="$SCRIPT_DIR/../../$DIR"
    if [ -d "$DIR_PATH" ]; then
        find "$DIR_PATH" -type f \( -name "*.h" -o -name "*.hpp" -o -name "*.c" -o -name "*.cpp" -o -name "*.m" -o -name "*.mm" \) -exec $CLANG_FORMAT -style=file:"$CLANG_FORMAT_FILE" -i {} +
    else
        echo "Directory not found: $DIR_PATH"
    fi
done < "$DIR_LIST"

echo "All files formatted."
