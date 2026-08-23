#!/usr/bin/env python3
"""Exercise 0: Entering the Matrix - virtual environment detection."""

import os
import site
import sys


def in_virtual_env() -> bool:
    """Return True if the interpreter is running inside a virtual env."""
    return sys.prefix != sys.base_prefix or bool(os.environ.get("VIRTUAL_ENV"))


def get_venv_name(venv_path: str) -> str:
    """Return the directory name of a virtual environment path."""
    return os.path.basename(os.path.normpath(venv_path))


def get_site_packages() -> list[str]:
    """Return the site-packages directories, falling back to the user one."""
    try:
        return list(site.getsitepackages())
    except AttributeError:
        return [site.getusersitepackages()]


def print_outside_matrix() -> None:
    print("MATRIX STATUS: You're still plugged in")
    print()
    print(f"Current Python: {sys.executable}")
    print("Virtual Environment: None detected")
    print()
    print("WARNING: You're in the global environment!")
    print("The machines can see everything you install.")
    print()
    print("To enter the construct, run:")
    print("python -m venv matrix_env")
    print("source matrix_env/bin/activate  # On Unix")
    print("matrix_env\\Scripts\\activate     # On Windows")
    print()
    print("Then run this program again.")
    print()
    print("Global package installation path(s):")
    for path in get_site_packages():
        print(f"  {path}")


def print_inside_construct(venv_path: str) -> None:
    venv_name = get_venv_name(venv_path)
    print("MATRIX STATUS: Welcome to the construct")
    print()
    print(f"Current Python: {sys.executable}")
    print(f"Virtual Environment: {venv_name}")
    print(f"Environment Path: {venv_path}")
    print()
    print("SUCCESS: You're in an isolated environment!")
    print("Safe to install packages without affecting")
    print("the global system.")
    print()
    print("Package installation path:")
    for path in get_site_packages():
        print(f"  {path}")


def main() -> int:
    try:
        venv_path = os.environ.get("VIRTUAL_ENV")
        if venv_path or in_virtual_env():
            print_inside_construct(venv_path or sys.prefix)
        else:
            print_outside_matrix()
    except OSError as error:
        print(f"ERROR: Unable to inspect the environment: {error}",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
