#ifndef EMSCRIPTEN_H
#define EMSCRIPTEN_H
#define EMSCRIPTEN_KEEPALIVE
#define EM_JS(ret, name, args, ...) ret name args { }
#define EM_ASYNC_JS(ret, name, args, ...) ret name args { }
#endif
