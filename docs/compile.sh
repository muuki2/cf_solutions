#!/bin/bash

# Compile the documentation
make clean
make all

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    
    # Try to open the PDF with the default PDF viewer
    if [ "$(uname)" == "Darwin" ]; then
        # macOS
        open build/main.pdf
    elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
        # Linux
        xdg-open build/main.pdf
    else
        echo "Please open build/main.pdf manually"
    fi
else
    echo "Compilation failed. Check the error messages above."
fi 