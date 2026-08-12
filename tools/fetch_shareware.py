#!/usr/bin/env python3
"""Download verified shareware data for optional PixelRAM game ports."""

from __future__ import annotations

import argparse
import hashlib
import shutil
import sys
import tarfile
import tempfile
import urllib.request
from pathlib import Path

USER_AGENT = "PixelRAM shareware fetcher/1.0"

DOOM_URL = "https://sources.debian.org/src/doom-wad-shareware/1.9.fixed-5/doom1.wad"
DOOM_SHA256 = "1d7d43be501e67d927e415e0b8f3e29c3bf33075e859721816f652a526cac771"

DESCENT_URL = "https://icculus.org/d2x/data/desc14sw.tar.gz"
DESCENT_ARCHIVE_SHA256 = "8b65eda01d03401d7a2dc71976528fbb7e0b07a93ce8ee0a9f1d9103623ae249"
DESCENT_FILES = {
    "DESCENT.HOG": (
        "descent.hog",
        "26d1e31e7709dfe6dddf17ccd37f5c82e866dce49a0faf07e90ba3213b288eab",
    ),
    "DESCENT.PIG": (
        "descent.pig",
        "b67865e513452a35887a20270d17fdfb5af1a2edaaae247bc523489f1d84f9ac",
    ),
}


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


def fetch_descent(directory: Path) -> None:
    directory.mkdir(parents=True, exist_ok=True)
    outputs = {name: directory / output for name, (output, _) in DESCENT_FILES.items()}

    if all(path.is_file() for path in outputs.values()):
        try:
            for source_name, path in outputs.items():
                verify(path, DESCENT_FILES[source_name][1])
            print(f"Descent shareware data ready: {directory}")
            return
        except RuntimeError:
            for path in outputs.values():
                path.unlink(missing_ok=True)

    archive = directory / "desc14sw.tar.gz"
    download(DESCENT_URL, archive, DESCENT_ARCHIVE_SHA256)

    wanted = {name.upper(): name for name in DESCENT_FILES}
    found: set[str] = set()
    with tarfile.open(archive, "r:gz") as tar:
        for member in tar.getmembers():
            basename = Path(member.name).name.upper()
            if basename not in wanted or not member.isfile():
                continue
            source_name = wanted[basename]
            stream = tar.extractfile(member)
            if stream is None:
                continue
            output_name, expected = DESCENT_FILES[source_name]
            output = directory / output_name
            with output.open("wb") as handle:
                shutil.copyfileobj(stream, handle)
            verify(output, expected)
            found.add(source_name)

    missing = set(DESCENT_FILES) - found
    if missing:
        raise RuntimeError("Shareware archive is missing: " + ", ".join(sorted(missing)))

    print(f"Descent shareware data ready: {directory}")


def main() -> int:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest="game", required=True)

    doom = subparsers.add_parser("doom")
    doom.add_argument("destination", type=Path)

    descent = subparsers.add_parser("descent")
    descent.add_argument("directory", type=Path)

    args = parser.parse_args()
    try:
        if args.game == "doom":
            fetch_doom(args.destination)
        else:
            fetch_descent(args.directory)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
