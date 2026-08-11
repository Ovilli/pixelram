/* Load the original DOOM WAD as a normal browser file, not inside Wasm/.data. */
Module.preRun = Module.preRun || [];
Module.preRun.push(function () {
    FS.createPreloadedFile('/', 'doom1.wad', 'doom1.wad', true, false);
});
