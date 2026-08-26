# ABOUTME: Custom exceptions used to keep error handling explicit and messages user-facing.

"""Project-specific exception hierarchy.

Brief
-----
Every error this project raises *on purpose* (as opposed to a genuine bug) is a
subclass of :class:`CallMeMaybeError`. Centralizing them here means the rest of
the codebase, and `cli.py` in particular, can catch one base class and always
print a clear, user-facing message instead of letting a raw traceback leak out
(the subject explicitly requires the program to "never crash unexpectedly").
"""

from __future__ import annotations


class CallMeMaybeError(Exception):
    """Base class for every error this project raises on purpose.

    Catching this (instead of a bare ``Exception``) anywhere in the codebase
    means "this is an anticipated failure with a message worth showing the
    user", as opposed to a genuine bug.
    """


class InputFileError(CallMeMaybeError):
    """Raised when an input file is missing, unreadable, or not valid JSON."""


class SchemaValidationError(CallMeMaybeError):
    """Raised when parsed JSON does not match the expected pydantic schema."""


class GenerationError(CallMeMaybeError):
    """Raised when the constrained decoder cannot make progress (e.g. every
    candidate token is masked out, which would indicate a bug in the grammar
    or a vocabulary that lacks a needed token)."""
