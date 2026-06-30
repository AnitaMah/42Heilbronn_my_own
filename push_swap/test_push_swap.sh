#!/bin/bash

# Configuration
EXECUTABLE="./push_swap"
STRATEGY="--complex"
OUTPUT="results.csv"

# Remove old results and initialize CSV
rm -f $OUTPUT
echo "size,duration_ms" > $OUTPUT

echo "Testing and saving results to $OUTPUT..."

# Loop from 10 to 6000 in steps of 10
for n in {10..6000..10}; do
    # Generate random numbers
    shuf -i 1-1000000 -n "$n" > nums.txt

    # Capture execution time in milliseconds
    # Note: Assumes your program outputs the duration to stdout or stderr
    # If your bench.c handles this internally, just run:
    # $EXECUTABLE $STRATEGY $(cat nums.txt) >> $OUTPUT

    start_time=$(date +%s%3N)
    $EXECUTABLE $STRATEGY $(cat nums.txt) > /dev/null
    end_time=$(date +%s%3N)

    duration=$((end_time - start_time))

    # Save to CSV
    echo "$n,$duration" >> $OUTPUT
    echo "Tested size: $n | Duration: ${duration}ms"
done

# Cleanup
rm -f nums.txt
echo "Done! Data saved to $OUTPUT"
