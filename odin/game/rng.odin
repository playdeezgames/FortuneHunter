package game

// The game's own generator (splitmix64), so a seed gives the same rolls on every target and tests can seed it.
// The C++ game used rand() % n; this replaces it, so levels differ from the original for the same seed by design.

Rng :: struct { state: u64 }

rng_seed :: proc(r: ^Rng, seed: u64) { r.state = seed }

rng_next :: proc(r: ^Rng) -> u64 {
	r.state += 0x9E3779B97F4A7C15
	z := r.state
	z = (z ~ (z >> 30)) * 0xBF58476D1CE4E5B9
	z = (z ~ (z >> 27)) * 0x94D049BB133111EB
	return z ~ (z >> 31)
}

// A uniform integer in [0, n) without modulo bias (the original's GenerateRandomNumberFromRange(0, n)). Requires n > 0.
rng_below :: proc(r: ^Rng, n: int) -> int {
	span := u64(n)
	limit := (max(u64) / span) * span
	for {
		x := rng_next(r)
		if x < limit { return int(x % span) }
	}
}

// A uniform integer in [lo, hi) (the original's GenerateRandomNumberFromRange(lo, hi)). Requires lo < hi.
rng_range :: proc(r: ^Rng, lo, hi: int) -> int { return lo + rng_below(r, hi - lo) }
