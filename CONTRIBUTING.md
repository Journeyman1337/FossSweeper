<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>

SPDX-License-Identifier: GPL-3.0-or-later
-->

# FossSweeper Contributing Guidelines

This file explains how to contribute to the FossSweeper project. For standards of behaviour, look at our [Code of Conduct](CODE_OF_CONDUCT.md).

TODO table of contents

## How to Report a Bug

Report bugs in the [issues board](https://www.github.com/Journeyman-dev/FossSweeper/issues). Before posting your own issue thread, [search if someone already reported the bug before you](https://docs.github.com/en/search-github/searching-on-github/searching-issues-and-pull-requests#search-by-the-title-body-or-comments). If a related issue doesn't exist, [create a new issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue) in the board with the `Bug Report` template and follow the instructions.

## How to Suggest a Feature

Suggest features in the [Ideas](https://www.github.com/Journeyman-dev/FossSweeper/discussions/categories/ideas) category of the discussions board.

## How to Ask a Question

Ask questions in the [Q&A](https://www.github.com/Journeyman-dev/FossSweeper/discussions/categories/q&a) category of the discussions board.

## How to Contribute Code Changes

Browse the [issues board](https://www.github.com/Journeyman-dev/FossSweeper/issues) to find an issue that interests you. If you want to work on an issue, say so by commenting in the issue thread. [Fork the dev branch](https://docs.github.com/en/get-started/quickstart/fork-a-repo#fork-an-example-repository) of the FossSweeper repository and [clone the fork](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) to your local machine. Initialize all git submodules within your local clone using the bash command `git submodule update --init --recursive` so you can build the project properly. [Commit your changes](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/making-changes-in-a-branch/committing-and-reviewing-changes-to-your-project) locally and then [push them](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/making-changes-in-a-branch/pushing-changes-to-github) to your forked repository. When you are ready, go ahead and [make a pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests) in the [FossSweeper pull requests board](https://github.com/Journeyman-dev/FossSweeper/pulls).

Every time you push changes to GitHub, several tests will automatically run using [GitHub Actions](https://docs.github.com/en/actions). Before your pull request can be merged into FossSweeper, all of these tests must pass.

### Unit Tests with Catch2

Many aspects of FossSweeper are tested automatically using the [Catch2](https://github.com/catchorg/Catch2) unit testing framework. Depending on what code you added or modified, you may be required to add more unit tests or change existing ones. If you are not sure test you need to workon, ask for guidance in your pull request thread.

### Manual Integration Testing

Unit tests are not enough to catch everything that can go wrong with FossSweeper. Depending on what code you modify, you may be told that you need to run FossSweeper on one or more platforms to ensure that there are no visible bugs. You can emulate a different operating system than your own using [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine) software such as [Virtual Box](https://www.virtualbox.org/). If you don't want to do this yourself, add the `help-needed` tag to your pull request and for someone else to do it for you.

### Linting with Trunk

A consistent coding style is maintained throughout the FossSweeper project. This is done through the use of multiple [code linting tools](https://en.wikipedia.org/wiki/Lint_(software)). To make it easier to manage the various linters used in the project, we use the [Trunk](https://trunk.io/products/check) amalgimated linting tool. If you have trunk installed on your machine, you can run the run the linter using the bash command `trunk fmt -a`.

### Licensing with REUSE

The FossSweeper project is a propoenent of the [REUSE Specification](https://reuse.software/spec/). This means that all files in the repository must be adequatly licensed for the your fork to be considered [REUSE-compliant](https://reuse.software/tutorial/). If you have the [REUSE Tool](https://github.com/fsfe/reuse-tool) installed on your computer, you can check your fork to see if it is compliant using the bash command `reuse lint`.


