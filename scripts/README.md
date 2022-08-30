<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>

SPDX-License-Identifier: GPL-3.0-or-later
-->

# Building

Building this project is designed to be a straightforward process. Use these convenience scripts located in the scripts folder to do most common tasks. These scripts should be executed from the root directory of the repository.

## Requirements

These scripts assume you have the following applications installed on your computer:

- CMake
- git
- Bourne Again SHell (bash)
- trunk

If you are using a Windows operating system, be sure that these applications are added to the PATH environmental variable.

## All in one generator scripts

Use the scripts "generate_with_test.bash" and "generate_no_tests.bash" in order to do everything required to generate a monolitic project with or without the automatic test framework. These scripts ensure that all required submodules are aquired and then generate projects using CMake.

## Linux package installer scripts

To build on Linux, multiple development packages need to be pre-installed on your system. Use the "install_ubuntu_packages.bash" or "install_fedora_packages.bash" scripts to install packages on either the Ubuntu or Fedora Linux distributions.

## Script for reseting the project to factory state

Call the "reset.bash" script in order to reset everything within the repository back to the state it is in the official fork hosted on GitHub. This will delete the build folder and remove all git submodules.
