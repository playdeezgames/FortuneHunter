#+build js
package main

// Thin Odin side of the JS storage shim. Strings cross the boundary as (ptr, len) pairs.
foreign import storage_env "storage"

@(default_calling_convention = "contextless")
foreign storage_env {
	js_storage_set    :: proc(key, value: string) -> bool ---
	js_storage_len    :: proc(key: string) -> int ---              // UTF-8 byte length, -1 if missing
	js_storage_get    :: proc(key: string, buf: []byte) -> int --- // bytes written, -1 if missing/too small
	js_storage_remove :: proc(key: string) ---
}

storage_set :: proc(key, value: string) -> bool { return js_storage_set(key, value) }
storage_remove :: proc(key: string) { js_storage_remove(key) }
storage_get :: proc(key: string, allocator := context.allocator) -> (value: string, ok: bool) {
	n := js_storage_len(key)
	if n < 0 { return "", false }
	buf := make([]byte, n, allocator)
	if js_storage_get(key, buf) != n { delete(buf, allocator); return "", false }
	return string(buf), true
}
