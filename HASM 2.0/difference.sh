#!/bin/bash

file1="$1"
file2="$2"
context=30  # number of bytes before and after the difference

if [[ ! -f "$file1" || ! -f "$file2" ]]; then
  echo "Usage: $0 file1.bin file2.bin"
  exit 1
fi

# Get first differing byte position (or EOF)
cmp_output=$(cmp -l "$file1" "$file2" | head -n1)
offset=$(echo "$cmp_output" | awk '{print $1}')

if [[ -z "$offset" ]]; then
  echo "✅ Files are identical"
  exit 0
fi

# Adjust for 0-based offset in xxd
start=$((offset - context))
[[ $start -lt 0 ]] && start=0
length=$((context * 2))

echo "❗ First difference at byte $offset"
echo "📍 Showing $length bytes from offset $start"

# Dump and highlight hex from both files
echo -e "\n🔹 Bytes from $file1:"
xxd -s "$start" -l "$length" "$file1"

echo -e "\n🔸 Bytes from $file2:"
xxd -s "$start" -l "$length" "$file2"
