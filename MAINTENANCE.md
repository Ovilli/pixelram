Before tagging a later release:

1. Update `PIXELRAM_VERSION_*` and `PIXELRAM_VERSION` in `pixelram.h`.
2. Update the pinned-version examples in `README.md` and `docs/distribution.md` if appropriate.
3. Add the release notes to `CHANGELOG.md`.
4. Run `make palettes` and commit generated changes.
5. Build and run the native examples with the supported raylib toolchain.
6. Build at least one WebAssembly example with Asyncify enabled.
7. Tag the exact commit used by teaching material.
