#!/usr/bin/env python
import json
from pathlib import Path
import subprocess

if __name__ == "__main__":
    settings_file = Path(__file__).parent.parent / ".vscode" / "settings.json"
    settings = json.loads(settings_file.read_text())

    if Path("/.env").exists() or Path("/.envrc").exists():
        raise RuntimeError("Refusing to run with direnv file in root directory")

    direnv_variables = json.loads(
        subprocess.check_output(
            ["direnv", "exec", "/", "direnv", "export", "json"]
        ).decode()
    )
    settings["cmake.environment"] = direnv_variables

    settings_file.write_text(json.dumps(settings, indent=4))
