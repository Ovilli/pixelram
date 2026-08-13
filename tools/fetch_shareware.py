#!/usr/bin/env python3
"""Download verified DOOM shareware data for PixelRAM."""

from __future__ import annotations

import argparse
import hashlib
import shutil
import sys
import tempfile
import urllib.request
from pathlib import Path

USER_AGENT = "PixelRAM shareware fetcher/1.0"

DOOM_URL = "https://sources.debian.org/src/doom-wad-shareware/1.9.fixed-5/doom1.wad"
DOOM_SHA256 = "1d7d43be501e67d927e415e0b8f3e29c3bf33075e859721816f652a526cac771"




def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def verify(path: Path, expected: str) -> None:
    actual = sha256(path)
    if actual != expected:
        raise RuntimeError(
            f"Checksum mismatch for {path.name}: expected {expected}, got {actual}"
        )


def download(url: str, destination: Path, expected: str) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.is_file():
        try:
            verify(destination, expected)
            return
        except RuntimeError:
            destination.unlink()

    print(f"Downloading {url}")
    request = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
    with urllib.request.urlopen(request) as response, tempfile.NamedTemporaryFile(
        dir=destination.parent, delete=False
    ) as temp:
        shutil.copyfileobj(response, temp)
        temp_path = Path(temp.name)

    try:
        verify(temp_path, expected)
        temp_path.replace(destination)
    except Exception:
        temp_path.unlink(missing_ok=True)
        raise


def fetch_doom(destination: Path) -> None:
    download(DOOM_URL, destination, DOOM_SHA256)
    print(f"DOOM shareware data ready: {destination}")



def main() -> int:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest="game", required=True)

    doom = subparsers.add_parser("doom")
    doom.add_argument("destination", type=Path)

    args = parser.parse_args()
    try:
        fetch_doom(args.destination)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
