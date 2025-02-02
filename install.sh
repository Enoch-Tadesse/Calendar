#!/bin/sh

set -e  # Exit if any command fails

# Define your GitHub repo and latest release URL
GITHUB_USER="Enoch-Tadesse"
REPO_NAME="Calendar"
INSTALL_DIR="/usr/local/bin"
BIN_NAME="ecal"

# Detect system architecture
ARCH=$(uname -m)
if [ "$ARCH" = "x86_64" ]; then
    FILE_NAME="ecal-linux-x86_64.exe"
elif [ "$ARCH" = "aarch64" ]; then
    # FILE_NAME="ecal-linux-arm64.exe"
    echo "Unsupported architecture: $ARCH"
    exit 1
else
    echo "Unsupported architecture: $ARCH"
    exit 1
fi

# Download the latest release from GitHub
echo "Downloading $BIN_NAME..."
curl -fsSL -o "$BIN_NAME" "https://github.com/$GITHUB_USER/$REPO_NAME/releases/latest/download/$FILE_NAME"

# Rename the file (Remove .exe extension)
mv "$BIN_NAME" "$BIN_NAME"

# Make it executable
chmod +x "$BIN_NAME"

# Move to /usr/local/bin
sudo mv "$BIN_NAME" "$INSTALL_DIR/$BIN_NAME"

# Verify installation
if command -v "$BIN_NAME" >/dev/null 2>&1; then
    echo "$BIN_NAME installed successfully! Run '$BIN_NAME' to start."
else
    echo "Installation failed."
    exit 1
fi
