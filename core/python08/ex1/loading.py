#!/usr/bin/env python3
"""Exercise 1: Loading Programs - pip vs Poetry dependency management."""

import importlib
import sys
from types import ModuleType
from typing import Any

REQUIRED_PACKAGES: dict[str, str] = {
    "pandas": "Data manipulation",
    "numpy": "Numerical computation",
    "matplotlib": "Visualization",
}


def try_import(name: str) -> ModuleType | None:
    """Import a module by name, returning None if it is unavailable."""
    try:
        return importlib.import_module(name)
    except ImportError:
        return None


def get_version(module: ModuleType) -> str:
    """Return a module's reported version, or 'unknown' if absent."""
    return str(getattr(module, "__version__", "unknown"))


def check_dependencies() -> dict[str, ModuleType | None]:
    """Import every known package and report its availability."""
    print("Checking dependencies:")
    modules: dict[str, ModuleType | None] = {}
    for name, purpose in REQUIRED_PACKAGES.items():
        module = try_import(name)
        modules[name] = module
        if module is not None:
            print(f"[OK] {name} ({get_version(module)}) - {purpose} ready")
        else:
            print(f"[MISSING] {name} - {purpose} unavailable")
    return modules


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


def simulate_matrix_data(
    pd: ModuleType, np: ModuleType, size: int = 1000
) -> Any:
    """Generate simulated Matrix data with numpy and wrap it in a frame."""
    rng = np.random.default_rng(seed=42)
    print(f"Processing {size} data points...")
    return pd.DataFrame(
        {
            "signal_strength": rng.normal(loc=50.0, scale=15.0, size=size),
            "anomaly_score": rng.uniform(low=0.0, high=1.0, size=size),
        }
    )


def visualize(matplotlib_module: ModuleType, frame: Any) -> str:
    """Render a histogram of the simulated data and save it to disk."""
    matplotlib_module.use("Agg")
    pyplot = importlib.import_module("matplotlib.pyplot")
    print("Generating visualization...")
    fig, ax = pyplot.subplots()
    ax.hist(frame["signal_strength"], bins=30)
    ax.set_title("Matrix Signal Strength Distribution")
    ax.set_xlabel("Signal Strength")
    ax.set_ylabel("Frequency")
    output_path = "matrix_analysis.png"
    fig.savefig(output_path)
    pyplot.close(fig)
    return output_path


def main() -> int:
    print("LOADING STATUS: Loading programs...")
    print()
    modules = check_dependencies()

    missing_required = [
        name for name in REQUIRED_PACKAGES if modules[name] is None
    ]
    if missing_required:
        print_missing_instructions(missing_required)
        compare_pip_poetry()
        return 1

    print()
    print("Analyzing Matrix data...")
    pandas_module = modules["pandas"]
    numpy_module = modules["numpy"]
    matplotlib_module = modules["matplotlib"]
    assert pandas_module is not None
    assert numpy_module is not None
    assert matplotlib_module is not None

    try:
        frame = simulate_matrix_data(pandas_module, numpy_module)
        output_path = visualize(matplotlib_module, frame)
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
