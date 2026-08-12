#!/usr/bin/env python3
"""Download and verify the free OpenTTD base graphics, sound and music sets."""

from __future__ import annotations

import hashlib
import shutil
import sys
import tempfile
import urllib.request
import zipfile
from pathlib import Path

PACKS = (
    (
        "OpenGFX 8.0",
        "https://cdn.openttd.org/opengfx-releases/8.0/opengfx-8.0-all.zip",
        "43a0c1dabf39cb865394f3a6cc36d4da5c10ecfaaf55652043104806810903be",
    ),
    (
        "OpenSFX 1.0.3",
        "https://cdn.openttd.org/opensfx-releases/1.0.3/opensfx-1.0.3-all.zip",
        "e0a218b7dd9438e701503b0f84c25a97c1c11b7c2f025323fb19d6db16ef3759",
    ),
    (
        "OpenMSX 0.4.2",
        "https://cdn.openttd.org/openmsx-releases/0.4.2/openmsx-0.4.2-all.zip",
        "5a4277a2e62d87f2952ea5020dc20fb2f6ffafdccf9913fbf35ad45ee30ec762",
    ),
)


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def download(url: str, destination: Path) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(url) as response, destination.open("wb") as output:
        shutil.copyfileobj(response, output)


def extract_flat(archive: Path, destination: Path) -> None:
    with zipfile.ZipFile(archive) as zf:
        for info in zf.infolist():
            if info.is_dir():
                continue
            name = Path(info.filename).name
            if not name:
                continue
            target = destination / name
            with zf.open(info) as source, target.open("wb") as output:
                shutil.copyfileobj(source, output)


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: fetch_openttd_assets.py DESTINATION")

    destination = Path(sys.argv[1]).resolve()
    marker = destination / ".pixelram-openttd-assets"
    if marker.exists():
        print(f"OpenTTD free base sets ready: {destination}")
        return

    destination.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="pixelram-openttd-") as temp_dir:
        temp = Path(temp_dir)
        for label, url, expected in PACKS:
            archive = temp / Path(url).name
            print(f"Downloading {label}...")
            download(url, archive)
            actual = sha256(archive)
            if actual != expected:
                raise SystemExit(
                    f"Checksum mismatch for {label}:\n"
                    f"  expected {expected}\n"
                    f"  got      {actual}"
                )
            extract_flat(archive, destination)

    marker.write_text("OpenGFX 8.0\nOpenSFX 1.0.3\nOpenMSX 0.4.2\n")
    print(f"OpenTTD free base sets ready: {destination}")


if __name__ == "__main__":
    main()
