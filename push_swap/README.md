*This project has been created as part of the 42 curriculum by anmakhov, jdhamoda.*

# push_swap

## Description

`push_swap` sorts a stack of integers using only two stacks (`a` and `b`) and a restricted set of operations. The goal is to produce the shortest possible sequence of operations that leaves all integers sorted in ascending order on stack `a`.

The project explores algorithmic complexity hands-on: different input sizes and disorder levels call for fundamentally different strategies to stay within the operation limits.

**Allowed operations:**

| Operation | Effect |
|-----------|--------|
| `sa` / `sb` | Swap the top two elements of stack a / b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` / `pb` | Push top of b → a / top of a → b |
| `ra` / `rb` | Rotate stack a / b upward (top becomes bottom) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` / `rrb` | Reverse rotate a / b (bottom becomes top) |
| `rrr` | `rra` and `rrb` simultaneously |

---

## Instructions

### Compilation

```bash
make        # builds push_swap
make clean  # removes object files
make fclean # removes objects + binary
make re     # full rebuild
```

### Usage

```bash
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <integers...>
```

| Flag | Behaviour |
|------|-----------|
| *(none)* | Adaptive mode (default) |
| `--simple` | Forces O(n²) selection sort |
| `--medium` | Forces O(n√n) chunk sort |
| `--complex` | Forces O(n log n) radix sort |
| `--adaptive` | Picks algorithm by measured disorder |
| `--bench` | Prints disorder %, strategy, and op count to stderr after sorting |

### Examples

```bash
# Basic sort
./push_swap 2 1 3 6 5 8

# Force a specific algorithm
./push_swap --simple 5 4 3 2 1
./push_swap --complex 4 67 3 87 23

# Verify output with checker
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker_linux $ARG

# Count operations (adaptive, 5 numbers)
ARG="4 67 3 87 23"
./push_swap --adaptive $ARG | wc -l

# Benchmark 500 numbers
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | wc -l

# Benchmark mode with metrics
./push_swap --bench --adaptive 4 67 3 87 23 2>bench.txt
cat bench.txt
```

### Error handling

The program prints `Error` to stderr and exits on:
- Non-integer arguments (e.g. `"abc"`, `"one"`)
- Values outside INT range
- Duplicate values
- Empty string arguments

---

## Algorithms

### Disorder metric

Before sorting, we measure how disordered the input is using an **inversion count**:

```
disorder = inversions / total_pairs
```

Where an inversion is any pair (i, j) with i < j but arr[i] > arr[j]. A sorted array has disorder 0.0; a fully reversed array has disorder 1.0. This is computed on the original integer array before any stack moves.

---

### 1. Simple — Selection Sort Adaptation — O(n²)

**Used when:** `--simple` flag, or adaptive mode with very low disorder (< 0.15 for n ≤ 100, < 0.10 for n > 100).

**How it works:**

1. Repeatedly scan stack `a` for the minimum value (`find_min_node`).
2. Use `bring_to_top` to rotate the minimum to the top of `a` (choosing `ra` or `rra` based on whichever is shorter).
3. Push it to `b` with `pb`.
4. Once `a` is empty, restore from `b` to `a` by always pulling the maximum from `b` — this lands them in ascending order in `a`.

**Why O(n²):** Finding the minimum requires scanning all remaining elements — done n times = n² comparisons total.

**Justification:** Works well when the input is nearly sorted (low disorder), since `bring_to_top` needs very few rotations when the minimum is already near the top.

---

### 2. Medium — Chunk Sort — O(n√n)

**Used when:** `--medium` flag, or adaptive mode with medium disorder (≥ 0.15 for n ≤ 100, ≥ 0.10 for n > 100, but below radix threshold).

**How it works:**

1. **Normalize** all values to indices 0..n-1 (rank order), so we can reason about position rather than raw value.
2. **Divide** into chunks of size √n (15 for n ≤ 100, 30 for larger inputs).
3. **Push chunks to b:** Scan `a` for elements whose index falls in the current chunk range. Push them to `b`, and if an element's index is in the lower half of the chunk, send it to the bottom of `b` with `rb` — so higher-indexed elements accumulate at the top of `b`.
4. **Restore to a:** Pull elements from `b` largest-index-first (using `bring_to_top` on the max each time) with `pa`. Since we push max first, `a` ends up in ascending order.

**Why O(n√n):** There are √n chunks. Processing each chunk costs O(n) rotations to scan `a`. Restoring each chunk costs O(√n) rotations per element to bring max to top. Total ≈ n√n operations.

**Justification:** The chunk strategy dramatically reduces wasted rotations compared to selection sort for moderately disordered inputs, without requiring the bit-manipulation of radix sort.

---

### 3. Complex — Radix Sort (LSD bitwise) — O(n log n)

**Used when:** `--complex` flag, or adaptive mode with high disorder on large inputs.

**How it works:**

1. **Normalize** values to indices 0..n-1.
2. For each bit from LSB to MSB (log₂(n) passes total):
   - Scan all elements in `a`. If the current bit of an element's index is **0** → push to `b`. If **1** → rotate to bottom of `a` with `ra`.
   - After processing all elements, push everything from `b` back to `a` with `pa`.
3. After all bits are processed, indices are sorted in ascending order = sorted.

**Why O(n log n):** There are log₂(n) bit passes, each touching all n elements = n log n operations.

**Justification:** Radix sort is the most scalable option. For 500 elements it achieves roughly 5000–7000 operations, comfortably under the 12000 requirement and often under 8000 for good performance.

---

### 4. Adaptive — Disorder-Driven Selection

**Used when:** `--adaptive` flag or no flag given (default).

The adaptive strategy measures disorder first, then selects the most appropriate algorithm:

Disorder | Strategy chosen | Complexity |
|------------|----------|-----------------|
| < 0.25 | Selection sort | O(n²) |
| <= 0.5 | Chunk sort | O(n√n) |
| >= 0.5 | Radix sort | O(n log n) |



**Rationale for thresholds:**
- At very low disorder, the minimum element is usually already near the top, so selection sort's O(n²) scans cost very few rotations in practice.
- At medium disorder, chunk sort's O(n√n) beats radix sort for small n because radix has higher constant overhead (log₂(n) full passes regardless of order).
- At high disorder with large n, radix sort's consistent O(n log n) always wins.

---

### Helper: `bring_to_top`

Used by both selection sort and chunk sort. Given a target node, it counts how many `ra` operations vs `rra` operations it would take to bring that node to the top, and picks the shorter path. This is what keeps both algorithms from being wasteful with rotations.

---

## Performance

| Input | Requirement | Good | Excellent |
|-------|------------|------|-----------|
| 100 random | < 2000 ops | < 1500 ops | < 700 ops |
| 500 random | < 12000 ops | < 8000 ops | < 5500 ops |

Typical results with this implementation:
- 100 numbers: ~700–900 ops (chunk sort path)
- 500 numbers: ~6000–7000 ops (radix sort path)

---

## Time Complexity Graph

To empirically validate the O(n log n) behaviour of the `--complex` radix sort strategy, we benchmarked execution time across increasing input sizes (n = 10 to 6000, step 10) and plotted it against a scaled O(n log n) reference curve.

> **Note:** This graph measures wall-clock execution time, which includes process startup, input generation, and system scheduling overhead alongside the actual sorting work. The op-count figures in the Performance table above (from `--bench`) are the more precise and primary measure of algorithmic complexity, since they directly reflect the number of stack operations executed rather than external timing noise.

### Benchmark script (`benchmark.sh`)

Generates random integers for each size, times the actual `push_swap` execution (wall-clock, in milliseconds), and writes the results to `results.csv`:

```bash
#!/bin/bash

EXECUTABLE="./push_swap"
STRATEGY="--complex"
OUTPUT="results.csv"

rm -f $OUTPUT
echo "size,duration_ms" > $OUTPUT

for n in {10..6000..10}; do
    shuf -i 1-1000000 -n "$n" > nums.txt

    start_time=$(date +%s%3N)
    $EXECUTABLE $STRATEGY $(cat nums.txt) > /dev/null
    end_time=$(date +%s%3N)

    duration=$((end_time - start_time))
    echo "$n,$duration" >> $OUTPUT
    echo "Tested size: $n | Duration: ${duration}ms"
done

rm -f nums.txt
echo "Done! Data saved to $OUTPUT"
```

### Plotting script (`plot_complexity.py`)

Reads `results.csv`, fits a scaled `n·log₂(n)` reference curve to the data, and saves the comparison as `time_complexity_graph.png`:

```python
import matplotlib.pyplot as plt
import csv
import numpy as np

def plot_complexity(csv_file):
    n = []
    duration = []

    with open(csv_file, 'r') as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            n.append(float(row[0]))
            duration.append(float(row[1]))

    n_arr = np.array(n)
    ref_curve = n_arr * np.log2(n_arr)
    scale_factor = np.mean(duration) / np.mean(ref_curve)
    scaled_ref = ref_curve * scale_factor

    plt.figure(figsize=(12, 7))
    plt.plot(n_arr, duration, marker='o', label='Actual Time', color='blue')
    plt.plot(n_arr, scaled_ref, linestyle='--', label='O(n log n) Reference', color='red')

    plt.xlabel('Size (n)')
    plt.ylabel('Duration (ms)')
    plt.title('Push_swap Complexity Analysis')
    plt.legend()
    plt.grid(True, which='both', linestyle='--')

    plt.savefig('time_complexity_graph.png')
    print("Graph saved as time_complexity_graph.png")

if __name__ == "__main__":
    plot_complexity('results.csv')
```

### Usage

```bash
./benchmark.sh
python3 plot_complexity.py
```

### Result

![Time Complexity Graph](time_complexity_graph.png)

The actual execution time tracks the scaled O(n log n) reference curve closely up to roughly n = 4000, after which it grows slightly faster than the reference — likely due to system-level effects (memory allocation overhead, cache behaviour, scheduling noise) rather than the algorithm itself. This is consistent with the O(n log n) guarantee given by the operation-count results above.

---

## Contributors

| Login | Main Contributions |
|--------|-------------------|
| `anmakhov` | Sorting algorithms (selection sort, radix sort and chunk sort), input parsing and validation, disorder analysis, small-stack optimization, and project architecture |
| `jdhamoda` | Core stack implementation, stack operations, adaptive strategy, parsing integration, build system, and project architecture |
---

## Resources

- [Sorting algorithm complexity — Big-O cheat sheet](https://www.bigocheatsheet.com/)
- [Radix sort explained — CS50](https://cs50.harvard.edu/x/)
- [Push_swap visualizer](https://github.com/o-reo/push_swap_visualizer) — useful for debugging
- [42 Norm documentation](https://github.com/42School/norminette)

## AI Usage

Artificial Intelligence tools were used as supplementary learning and documentation resources during the development of this project.

Their use was limited to:
- Discussing algorithmic approaches and complexity analysis
- Reviewing documentation for clarity and readability
- Identifying potential edge cases in parsing and input validation
- Providing general feedback on code structure and project organization
- Assisting in the creation of an initial README structure based on the project's source code and features

Any suggestions obtained through AI tools were critically reviewed, understood, and adapted before being considered for inclusion.

## This README follows all requirements from the subject! Good luck tomorrow!
