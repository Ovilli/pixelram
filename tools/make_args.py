#!/usr/bin/env python3
import json
import sys

if len(sys.argv) < 2:
    raise SystemExit("usage: make_args.py OUTPUT [arg ...]")

output = sys.argv[1]
defaults = sys.argv[2:]

js_defaults = json.dumps(defaults)

script = f"""
(function() {{
  var defaults = {js_defaults};

  function storageKey() {{
    return 'pixelram-args:' + location.pathname;
  }}

  var args = defaults.slice();

  try {{
    var stored = sessionStorage.getItem(storageKey());

    if (stored !== null) {{
      /*
       * A console Run/Enter override is intentionally one-shot:
       * consume it for this startup and remove it immediately.
       */
      sessionStorage.removeItem(storageKey());

      var parsed = JSON.parse(stored);
      if (Array.isArray(parsed)) {{
        args = parsed.map(String);
      }}
    }}
  }} catch (_) {{
    /* If sessionStorage is unavailable, simply use Makefile defaults. */
  }}

  Module = Module || {{}};
  Module.arguments = args.slice();

  var oldPreRun = Module.preRun;
  if (!Array.isArray(oldPreRun)) {{
    oldPreRun = oldPreRun ? [oldPreRun] : [];
  }}

  oldPreRun.push(function() {{
    var candidates = Array.from(new Set(
      Module.arguments.filter(function(arg) {{
        return arg &&
               arg.charAt(0) !== '-' &&
               arg.indexOf('://') === -1 &&
               arg.charAt(0) !== '/';
      }})
    ));

    candidates.forEach(function(name) {{
      var dep = 'pixelram-file:' + name;
      addRunDependency(dep);

      fetch(name, {{cache: 'no-store'}})
        .then(function(response) {{
          if (!response.ok) throw new Error(String(response.status));
          return response.arrayBuffer();
        }})
        .then(function(buffer) {{
          var normalized = name.replace(/^\\.\\//, '');
          var slash = normalized.lastIndexOf('/');
          var dir = slash >= 0 ? normalized.slice(0, slash) : '';

          if (dir) {{
            var path = '';
            dir.split('/').forEach(function(part) {{
              if (!part) return;
              path += '/' + part;
              try {{ FS.mkdir(path); }} catch (_) {{}}
            }});
          }}

          FS.writeFile('/' + normalized, new Uint8Array(buffer));
        }})
        .catch(function() {{
          /* A non-file argument is perfectly valid; leave it as argv only. */
        }})
        .finally(function() {{
          removeRunDependency(dep);
        }});
    }});
  }});

  Module.preRun = oldPreRun;

  if (typeof window !== 'undefined') {{
    window.PIXELRAM_ARGS = Module.arguments.slice();
    window.dispatchEvent(new Event('pixelram-args-ready'));
  }}
}})();
"""

with open(output, "w", encoding="utf-8") as f:
    f.write(script)
