#!/usr/bin/env python3
"""Exercise 0: Stocking the Reagents - pip vs Poetry dependency management."""

import importlib
import sys

REQUIRED_PACKAGES: dict[str, str] = {
    "pandas": "Data manipulation",
    "numpy": "Numerical computation",
}


def get_version(name: str) -> str | None:
    """Return an installed package's version, or None if it is missing."""
    try:
        module = importlib.import_module(name)
    except ImportError:
        return None
    return str(getattr(module, "__version__", "unknown"))


def check_dependencies() -> list[str]:
    """Report every known reagent and return the names of missing ones."""
    print("Checking dependencies:")
    missing: list[str] = []
    for name, purpose in REQUIRED_PACKAGES.items():
        version = get_version(name)
        if version is not None:
            print(f"[OK] {name} ({version}) - {purpose} ready")
        else:
            print(f"[MISSING] {name} - {purpose} unavailable")
            missing.append(name)
    return missing


def print_missing_instructions(missing: list[str]) -> None:
    print()
    print(f"Missing reagents: {', '.join(missing)}")
    print()
    print("Install with pip:")
    print("  pip install -r ex0/requirements.txt")
    print()
    print("Install with Poetry:")
    print("  poetry install")
    print("  poetry run python ex0/loading.py")


def compare_pip_poetry() -> None:
    print()
    print("pip vs Poetry:")
    print("  requirements.txt declares what to install; pip resolves it "
          "at install time.")
    print("  pyproject.toml declares the same constraints, and Poetry "
          "pins the resolved")
    print("  versions in poetry.lock so every install is identical.")


def main() -> int:
    print("REAGENT STATUS: Loading reagents...")
    print()
    missing = check_dependencies()
    if missing:
        print_missing_instructions(missing)
        compare_pip_poetry()
        return 1

    compare_pip_poetry()
    print()
    print("All reagents present and accounted for.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
