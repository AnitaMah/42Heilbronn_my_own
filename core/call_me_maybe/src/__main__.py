# ABOUTME: Enables `uv run python -m src ...` / `python -m src ...` as required by the subject.

"""Module entry point so ``python -m src`` runs :func:`src.cli.main`."""

import sys

from .cli import main

if __name__ == "__main__":
    sys.exit(main())
