# Map Editor

## Description

This is a map generator using the **Tkinter** library to create a graphical user interface (GUI). The application allows users to generate their own maps with various configurations and options.

---

## Table of contents

-   [Prerequisites](#Prerequisites)
-   [MacOs Installation Guide](#macOs-Installation-Guide)
-   [Linux Installation Guide](#Linux-Installation-Guide-Ubuntu)

---

## Prerequisites

Before you begin, ensure that you have the following installed:

- **Python 3.x** (recommended version: 3.8 or higher)
- **Tkinter** (comes pre-installed with Python)
- **pip** (Python package manager)
- **pillow** (recommended version: 8.0.0 or higher)
- **Tkmacos** (only for macOS)

---

## Check Python and Tkinter Installation

To verify if Python and Tkinter are installed, run the following commands in your terminal:

```bash
python3 --version
python3 -m tkinter
```

---

## macOS Installation Guide

### Step 1: Install Python (if necessary)

If Python is not installed, or if you want to use a different version, you can install it via Homebrew:

1. Install Homebrew (if not already installed):

    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. Install Python using Homebrew:

    ```bash
    brew install python
    ```

### Step 2: Create and Activate a Virtual Environment

1. Create a virtual environment:

    ```bash
    python3 -m venv map_editor_env
    ```

2. Activate the virtual environment:

    ```bash
    source map_editor_env/bin/activate
    ```

### Step 3: Install Tkinter (if necessary)

Tkinter usually comes pre-installed with Python on macOS. If it is not installed, you can install it with:
    
```bash
  brew install python-tk
```

### Step 4: Install pip (if necessary)

If you encounter the error zsh: command not found: pip, install pip manually:

1. Download the get-pip.py script:

    ```bash
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    ```

2. Install pip using Python:

    ```bash
    python3 get-pip.py
    ```

3. Verify that pip is installed:

    ```bash
    pip3 --version
    ```

### Step 5: Install Tkmacos (if necessary)

Inside the activated virtual environment, run:

```bash
  pip3 install tkmacosx
```

### Step 6: Install Pillow

```bash
  pip install Pillow
```

### Step 7: Run the Application

```bash
  cd map-editor/macos
  python3 map_editor
```

---

## Linux Installation Guide (Ubuntu)

### Step 1: Install Python (if necessary)

On most Linux distributions, Python is pre-installed. To check the installed version:

```bash
  python3 --version
```

If it's not installed, you can install it using the package manager for your distribution.

```bash
  sudo apt update
  sudo apt install python3
```

### Step 2: Install Tkinter (if necessary)

Tkinter is usually included with Python. If you need to install it, use the following command :

```bash
  sudo apt install python3-tk
```

### Step 3: Install pip (if necessary)

To install pip if it’s not already installed:

```bash
  sudo apt install python3-pip
```

Verify that pip is installed:

```bash
  pip3 --version
```

### Step 4: Install Pillow

```bash
  pip install Pillow
```

### Step 5: Run the Application

```bash
  cd map-editor/linux
  python3 map_editor
```

Once the map editor is launched, you can place your enemies and obstacles as you wish. Make sure to save your work in our project at this path: /server/maps/, and name your file “map1.map”.