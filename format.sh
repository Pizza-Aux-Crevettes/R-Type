#!/bin/bash

echo "Please select a project to format:"
echo "1) Network"
echo "2) GameEngine"
echo "3) Client"
echo "4) Exit"

read -p "Enter your choice [1-4]: " choice

case $choice in
    1)
        DIR="network"
        ;;
    2)
        DIR="game_engine"
        ;;
    3)
        DIR="client"
        ;;
    4)
        echo "Exiting."
        exit 0
        ;;
    *)
        echo "Invalid choice!"
        exit 1
        ;;
esac

if [ -d "$DIR" ]; then
    echo "Running clang-format in the '$DIR' directory..."
    find "$DIR" \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -i {} +
    echo "Formatting complete."
else
    echo "Directory '$DIR' does not exist."
    exit 1
fi
