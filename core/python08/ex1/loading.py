#!/usr/bin/env python3
"""Exercise 1: Loading Programs - pip vs Poetry dependency management."""

import importlib
import sys

REQUIRED_PACKAGES: dict[str, str] = {
    "pandas": "Data manipulation",
    "numpy": "Numerical computation",
    "matplotlib": "Visualization",
}


def get_version(name: str) -> str | None:
    """Return an installed package's version, or None if it is missing."""
    try:
        module = importlib.import_module(name)
    except ImportError:
        return None
    return str(getattr(module, "__version__", "unknown"))


def check_dependencies() -> list[str]:
    """Report every known package and return the names of missing ones."""
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
    print(f"Missing packages: {', '.join(missing)}")
    print()
    print("Install with pip:")
    print("  pip install -r requirements.txt")
    print()
    print("Install with Poetry:")
    print("  poetry install")
    print("  poetry run python loading.py")


def compare_pip_poetry() -> None:
    print()
    print("pip vs Poetry:")
    print("  pip    -> requirements.txt, you manage the venv yourself,")
    print("            no lock file by default, dependency versions")
    print("            resolve loosely at install time.")
    print("  Poetry -> pyproject.toml, creates/manages the venv for you,")
    print("            poetry.lock pins exact versions so installs are")
    print("            fully reproducible across machines.")


def run_analysis(size: int = 1000) -> str:
    """Simulate Matrix data with numpy, analyze it and save a plot."""
    import matplotlib
    import numpy as np
    import pandas as pd

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    rng = np.random.default_rng(seed=42)
    print(f"Processing {size} data points...")
    frame = pd.DataFrame(
        {
            "signal_strength": rng.normal(loc=50.0, scale=15.0, size=size),
            "anomaly_score": rng.uniform(low=0.0, high=1.0, size=size),
        }
    )

    print("Generating visualization...")
    fig, ax = plt.subplots()
    ax.hist(frame["signal_strength"], bins=30)
    ax.set_title("Matrix Signal Strength Distribution")
    ax.set_xlabel("Signal Strength")
    ax.set_ylabel("Frequency")
    output_path = "matrix_analysis.png"
    fig.savefig(output_path)
    plt.close(fig)
    return output_path


def main() -> int:
    print("LOADING STATUS: Loading programs...")
    print()
    missing = check_dependencies()
    if missing:
        print_missing_instructions(missing)
        compare_pip_poetry()
        return 1

    print()
    print("Analyzing Matrix data...")
    try:
        output_path = run_analysis()
    except (ValueError, OSError) as error:
        print(f"ERROR: Analysis failed: {error}", file=sys.stderr)
        return 1

    print()
    print("Analysis complete!")
    print(f"Results saved to: {output_path}")

    compare_pip_poetry()
    return 0


if __name__ == "__main__":
    sys.exit(main())
