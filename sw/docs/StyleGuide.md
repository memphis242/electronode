# Electronode Style Guide

This repository uses a small set of local style conventions for generated
firmware code and related docs.

## C++ and Namespace Layout

- Use C++20 for firmware application code.
- Prefer namespaces over free-form module prefixes, for example
  `electronode::supervisor::start()`, `electronode::acq::emg::start()`, and
  `electronode::processing::imu::start()`.
- Keep module APIs thin while a module has one static Zephyr-backed instance;
  introduce a class only when multiple instances or constructor-owned state are
  needed.
- App-specific headers use the `.hpp` extension.

## Headers and Comments

- Use `#pragma once` in app headers.
- Use Doxygen file headers with `@file`, `@brief`, `@author`, and `@date`.
- Wrap Doxygen comment lines with the continuation text aligned under the first
  word after the `@brief` tag.
- Avoid awkward one-word wrap fragments in comments if that would make the text
  less readable.

## Naming

- Use `s_` for file-scope static variables and static storage objects.
- Use uppercase `constexpr` names for app-level constants, for example
  `EMG_SAMPLE_HZ` and `PACKET_QUEUE_DEPTH`.

## Formatting

- Use spaces only, no tabs.
- Indent with 3 spaces.
- Keep zero-argument calls as `foo()`.
- For calls and macros with 3 or more arguments, wrap them vertically and align
  the arguments.
- For 1 or 2 arguments, keep the call on one line unless it would exceed the
  80-character limit by more than about 5 characters.
- The 80-character width limit takes precedence when a line would otherwise
  become noisy or hard to scan.

## Source Style

- Keep Zephyr kernel object and logging macros formatted consistently with the
  surrounding call-style rules.
- Preserve the separation between public module functions and local helper
  implementations in each source file.

