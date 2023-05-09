#!/bin/bash

# Define the directory where the input text files are located
input_dir="inputs"

# Define the directory where the compressed files will be saved
output_dir="outputs"

# Create the output directory if it does not already exist
mkdir -p "$output_dir"

# Loop through each file in the input directory
for file in "$input_dir"/*.txt; do
  # Get the filename without the extension
  filename="$(basename -- "$file" .txt)"

  # Compress the input file and save the output file in the output directory
  python lz78.py -c "$file" -o "$output_dir/$filename.z78"

  # Get the sizes of the original and compressed files
  original_size=$(stat -c%s "$file")
  compressed_size=$(stat -c%s "$output_dir/$filename.z78")

  # Calculate the compression ratio
  ratio=$(bc -l <<< "scale=2; $original_size / $compressed_size")

  # Print the results to the console
  echo "File: $filename.txt"
  echo "Original size: $original_size bytes"
  echo "Compressed size: $compressed_size bytes"
  echo "Compression ratio: $ratio"
  echo
done