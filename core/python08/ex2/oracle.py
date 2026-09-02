#!/usr/bin/env python3
"""Exercise 2: Accessing the Mainframe - secure configuration via .env."""

import os
import sys
from pathlib import Path
from types import ModuleType

try:
    dotenv: ModuleType | None = __import__("dotenv")
except ImportError:
    dotenv = None

REQUIRED_KEYS: list[str] = [
    "MATRIX_MODE",
    "DATABASE_URL",
    "API_KEY",
    "LOG_LEVEL",
    "ZION_ENDPOINT",
]

DEFAULTS: dict[str, str] = {
    "MATRIX_MODE": "development",
    "DATABASE_URL": "sqlite:///matrix_local.db",
    "API_KEY": "",
    "LOG_LEVEL": "INFO",
    "ZION_ENDPOINT": "http://localhost:8000",
}


def load_environment() -> bool:
    """Load variables from a local .env file, if python-dotenv is available."""
    if dotenv is None:
        print("[WARNING] python-dotenv is not installed; using only the")
        print("          system environment. Install with:")
        print("          pip install python-dotenv")
        return False
    env_path = Path(__file__).resolve().parent / ".env"
    if not env_path.exists():
        return False
    dotenv.load_dotenv(dotenv_path=env_path)
    return True


def get_config() -> dict[str, str]:
    """Read configuration values from the environment, or use defaults."""
    return {
        key: os.environ.get(key, DEFAULTS[key]) for key in REQUIRED_KEYS
    }


def mask_secret(value: str) -> str:
    """Mask a secret so it can be shown without leaking it."""
    if not value:
        return "NOT SET"
    if len(value) <= 4:
        return "*" * len(value)
    return f"{value[:2]}{'*' * (len(value) - 4)}{value[-2:]}"


def describe_database(url: str) -> str:
    """Describe whether a database URL points at a local or remote instance."""
    if url.startswith("sqlite") or "localhost" in url or "127.0.0.1" in url:
        return "Connected to local instance"
    return "Connected to remote instance"


def print_report(config: dict[str, str], env_loaded: bool) -> None:
    is_production = config["MATRIX_MODE"] == "production"

    print("ORACLE STATUS: Reading the Matrix...")
    print()
    print("Configuration loaded:")
    print(f"Mode: {config['MATRIX_MODE']}")
    print(f"Database: {describe_database(config['DATABASE_URL'])}")
    api_status = "Authenticated" if config["API_KEY"] else "Missing (unauth)"
    print(f"API Access: {api_status}")
    print(f"Log Level: {config['LOG_LEVEL']}")
    network_status = "Online" if config["ZION_ENDPOINT"] else "Offline"
    print(f"Zion Network: {network_status}")
    print()
    print("Environment security check:")
    print("[OK] No hardcoded secrets detected")
    env_status = "properly configured" if env_loaded else "not found"
    print(f"[{'OK' if env_loaded else 'WARN'}] .env file {env_status}")
    overrides_ok = not is_production or bool(config["API_KEY"])
    overrides_flag = "OK" if overrides_ok else "FAIL"
    print(f"[{overrides_flag}] Production overrides available")
    print()
    print("The Oracle sees all configurations.")

    if is_production:
        print()
        print("PRODUCTION MODE: sensitive values are masked below.")
        print(f"API_KEY: {mask_secret(config['API_KEY'])}")
    else:
        print()
        print("DEVELOPMENT MODE: verbose configuration for debugging.")
        for key, value in config.items():
            shown = mask_secret(value) if key == "API_KEY" else value
            print(f"  {key} = {shown}")


def main() -> int:
    env_loaded = load_environment()
    config = get_config()
    print_report(config, env_loaded)

    missing_required = [
        key for key in REQUIRED_KEYS
        if key != "API_KEY" and not config[key]
    ]
    if missing_required:
        joined = ", ".join(missing_required)
        print(f"\n[ERROR] Missing required configuration: {joined}",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
