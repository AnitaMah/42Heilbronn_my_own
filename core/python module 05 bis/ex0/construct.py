#!/usr/bin/env python3
"""Exercise 0: The Sealed Laboratory - virtual environment detection."""

import os
import site
import sys


def in_virtual_env() -> bool:
    """Return True if the interpreter is running inside a virtual env."""
    return sys.prefix != sys.base_prefix or bool(os.environ.get("VIRTUAL_ENV"))


def get_venv_name(venv_path: str) -> str:
    """Return the directory name of a virtual environment path."""
    return os.path.basename(os.path.normpath(venv_path))


def get_site_packages_path() -> str:
    """Return the current interpreter's primary site-packages directory."""
    try:
        packages = site.getsitepackages()
    except AttributeError:
        return site.getusersitepackages()
    return packages[0] if packages else site.getusersitepackages()


def print_outside_laboratory() -> None:
    print("LABORATORY STATUS: You are working in the open")
    print()
    print(f"Current Python: {sys.executable}")
    print("Virtual Environment: None detected")
    print()
    print("WARNING: You are in the global environment!")
    print("Every reagent you install here leaks into the whole system.")
    print()
    print("To seal the laboratory, run:")
    print("python3 -m venv lab_env")
    print("source lab_env/bin/activate # On Unix")
    print("lab_env\\Scripts\\activate  # On Windows")
    print()
    print("Then run this program again.")


def print_sealed_laboratory(venv_path: str) -> None:
    venv_name = get_venv_name(venv_path)
    print("LABORATORY STATUS: The laboratory is sealed")
    print()
    print(f"Current Python: {sys.executable}")
    print(f"Virtual Environment: {venv_name}")
    print(f"Environment Path: {venv_path}")
    print()
    print("SUCCESS: You are working in an isolated environment!")
    print("Safe to install reagents without affecting")
    print("the global system.")
    print()
    print("Reagent installation path:")
    print(get_site_packages_path())


def main() -> int:
    try:
        venv_path = os.environ.get("VIRTUAL_ENV")
        if venv_path or in_virtual_env():
            print_sealed_laboratory(venv_path or sys.prefix)
        else:
            print_outside_laboratory()
    except OSError as error:
        print(f"ERROR: Unable to inspect the environment: {error}",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
