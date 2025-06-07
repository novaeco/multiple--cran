#!/usr/bin/env python3
"""Provisioner script to ensure ESP-IDF setup is ready."""
import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SETUP = ROOT / "setup.sh"


def need_setup() -> bool:
    lvgl_dir = ROOT / "components" / "lvgl"
    if not lvgl_dir.exists():
        return True
    if "IDF_PATH" not in os.environ:
        return True
    try:
        subprocess.run(["idf.py", "--version"], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except (subprocess.CalledProcessError, FileNotFoundError):
        return True
    return False


def run_setup() -> None:
    subprocess.check_call(["bash", str(SETUP)])


def main() -> None:
    if need_setup():
        print("[Provisioner] Running setup.sh", flush=True)
        run_setup()
    else:
        print("[Provisioner] Environment already prepared", flush=True)


if __name__ == "__main__":
    main()
