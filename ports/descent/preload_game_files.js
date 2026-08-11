/* Load original Descent data files unchanged from beside descent.html. */
Module.preRun = Module.preRun || [];
Module.preRun.push(function () {
    FS.createPreloadedFile('/', 'descent.hog', 'descent.hog', true, false);
    FS.createPreloadedFile('/', 'descent.pig', 'descent.pig', true, false);
});
