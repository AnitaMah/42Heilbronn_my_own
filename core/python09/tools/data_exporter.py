"""Export generated Cosmic Data datasets to JSON, CSV, and Python formats.

Run directly to (re)populate generated_data/ with sample datasets for
all three exercises (ex0 SpaceStation, ex1 AlienContact, ex2 SpaceMission).
"""

from __future__ import annotations

import csv
import json
from pathlib import Path
from typing import Any

from data_generator import generate_dataset

GENERATED_DATA_DIR = Path(__file__).parent / "generated_data"


def export_json(data: list[dict[str, Any]], path: Path) -> None:
    path.write_text(json.dumps(data, indent=2, default=str))


def export_csv(data: list[dict[str, Any]], path: Path) -> None:
    if not data:
        path.write_text("")
        return
    fieldnames = list(data[0].keys())
    with path.open("w", newline="") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        for row in data:
            flat_row = {
                key: json.dumps(value) if isinstance(value, (list, dict)) else value
                for key, value in row.items()
            }
            writer.writerow(flat_row)


def export_python(data: list[dict[str, Any]], path: Path, variable_name: str) -> None:
    lines = [f"{variable_name} = ["]
    for row in data:
        lines.append(f"    {row!r},")
    lines.append("]")
    path.write_text("\n".join(lines) + "\n")


def main() -> None:
    GENERATED_DATA_DIR.mkdir(exist_ok=True)
    datasets = {
        "space_station": 15,
        "alien_contact": 15,
        "space_mission": 10,
    }
    for kind, count in datasets.items():
        data = generate_dataset(kind, count)
        plural = f"{kind}s"
        export_json(data, GENERATED_DATA_DIR / f"{plural}.json")
        export_csv(data, GENERATED_DATA_DIR / f"{plural}.csv")
        export_python(data, GENERATED_DATA_DIR / f"{plural}.py", f"{plural}_data")
        print(f"Exported {count} {kind} records -> {plural}.json / .csv / .py")


if __name__ == "__main__":
    main()
