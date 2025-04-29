genisoimage -o output.iso -R -J assembly
dd if=/dev/zero bs=1M count=1 >> output.iso