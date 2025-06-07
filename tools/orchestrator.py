#!/usr/bin/env python3
"""Orchestrator entry point triggering the Provisioner."""
import subprocess
from pathlib import Path
import sys

PROVISIONER = Path(__file__).with_name("provisioner.py")


def main() -> None:
    result = subprocess.run([sys.executable, str(PROVISIONER)])
    sys.exit(result.returncode)


if __name__ == "__main__":
    main()
