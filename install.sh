#!/bin/bash

# for x86_64 architecture
install_x86_64() {
    echo "Detected x86_64 architecture."
    curl -O https://raw.githubusercontent.com/Enoch-Tadesse/Calendar/main/releases/latest/download/ecal-linux-x86_64
    chmod +x ./ecal-linux-x86_64
    sudo cp ./ecal-linux-x86_64 /usr/bin/ecal
    sudo rm ./ecal-linux-x86_64
    echo "Installation for x86_64 completed."
}

# for arm64 architecture
install_arm64() {
    echo "Detected arm64 architecture."
    curl -O https://raw.githubusercontent.com/Enoch-Tadesse/Calendar/main/releases/latest/download/ecal-linux-arm64
    chmod +x ./ecal-linux-arm64
    sudo cp ./ecal-linux-arm64 /usr/bin/ecal
    sudo rm ./ecal-linux-arm64
    echo "Installation for arm64 completed."
}

main() {
    # Check the system architecture
    ARCH=$(uname -m)

    if [ "$ARCH" == "x86_64" ]; then
        install_x86_64
    elif [ "$ARCH" == "aarch64" ]; then
        install_arm64
    else
        echo "Unsupported architecture: $ARCH"
        echo "Try compiling and installing manually"
        exit 1
    fi
}

# Call the main function
main
