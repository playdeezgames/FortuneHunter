// Minimal localStorage shim for Odin (foreign module "storage"). Strings arrive as (ptr, len) pairs.
// Usage: odin.runWasm("x.wasm", null, storageImports(mem), mem) with mem = new odin.WasmMemoryInterface().
function storageImports(mem) {
	const enc = new TextEncoder();
	const key = (p, n) => mem.loadString(p, n);
	return {
		storage: {
			js_storage_set(kp, kn, vp, vn) {
				try { localStorage.setItem(key(kp, kn), mem.loadString(vp, vn)); return true; }
				catch (e) { console.warn("storage_set failed:", e.name); return false; }  // quota, disabled, etc.
			},
			js_storage_len(kp, kn) {
				let v; try { v = localStorage.getItem(key(kp, kn)); } catch (e) { return -1; }
				return v === null ? -1 : enc.encode(v).length;
			},
			js_storage_get(kp, kn, bp, bn) {
				let v; try { v = localStorage.getItem(key(kp, kn)); } catch (e) { return -1; }
				if (v === null) return -1;
				const bytes = enc.encode(v);
				if (bytes.length > bn) return -1;
				mem.loadBytes(bp, bn).set(bytes);
				return bytes.length;
			},
			js_storage_remove(kp, kn) { try { localStorage.removeItem(key(kp, kn)); } catch (e) {} },
		},
	};
}
