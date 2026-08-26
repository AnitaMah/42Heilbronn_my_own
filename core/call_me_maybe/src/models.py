# ABOUTME: Pydantic data models for function definitions, test prompts, and results.
# ABOUTME: Every class in this project is validated through pydantic, per the subject rules.

"""Pydantic schema for every JSON shape this project reads or writes.

Brief
-----
Three input/output shapes flow through the pipeline, and each gets its own
pydantic model with ``extra="forbid"`` so a typo or an unexpected key in a
JSON file fails fast with a specific validation error instead of silently
propagating:

* :class:`FunctionDefinition` -- one entry of ``function_definitions.json``
  (what functions exist, their parameters, and their types).
* :class:`TestPrompt` -- one entry of ``function_calling_tests.json`` (a
  natural-language request to resolve).
* :class:`FunctionCallResult` -- one entry of the final output file (the
  resolved ``{prompt, name, parameters}`` triple).
"""

from __future__ import annotations

from typing import Any, Literal

from pydantic import BaseModel, ConfigDict, Field, field_validator

# The three JSON scalar types this project's functions ever use as a parameter
# or return type. Booleans are supported by the grammar (see grammar.py's
# JSONBooleanStep) even though none of the sample functions currently use one.
JsonScalarType = Literal["number", "string", "boolean"]


class ParameterSpec(BaseModel):
    """Describes a single function parameter's expected JSON type."""

    model_config = ConfigDict(extra="forbid")

    type: JsonScalarType


class ReturnSpec(BaseModel):
    """Describes a function's return type."""

    model_config = ConfigDict(extra="forbid")

    type: JsonScalarType


class FunctionDefinition(BaseModel):
    """One entry from ``function_definitions.json``.

    Parameter order is preserved (Python dicts keep insertion order), which matters
    because the constrained decoder walks parameters in the order they are declared.
    """

    model_config = ConfigDict(extra="forbid")

    name: str = Field(min_length=1)
    description: str = Field(default="")
    parameters: dict[str, ParameterSpec] = Field(default_factory=dict)
    returns: ReturnSpec | None = None

    @field_validator("name")
    @classmethod
    def _name_must_be_identifier_like(cls, value: str) -> str:
        """Reject a function name that is empty or only whitespace.

        Parameters
        ----------
        value : str
            The raw ``name`` field being validated.

        Returns
        -------
        str
            The same value, unchanged, once it passes the check.
        """
        if not value.strip():
            raise ValueError("function name must not be blank")
        return value


class TestPrompt(BaseModel):
    """One entry from ``function_calling_tests.json``."""

    model_config = ConfigDict(extra="forbid")

    prompt: str = Field(min_length=1)


class FunctionCallResult(BaseModel):
    """One entry of the final output file: the resolved function call for a prompt."""

    model_config = ConfigDict(extra="forbid")

    prompt: str
    name: str
    parameters: dict[str, Any]
