#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

// Function to read the ELF file and extract section names
void read_text_section(FILE *in_file, size_t file_size) {
    // Read the ELF header
    Elf64_Ehdr ehdr;
    fseek(in_file, 0, SEEK_SET);
    fread(&ehdr, sizeof(Elf64_Ehdr), 1, in_file);
    
    // Verify the ELF magic number
    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Invalid ELF magic number.\n");
        return;
    }

    // Validate number of section headers
    if (ehdr.e_shnum == 0) {
        fprintf(stderr, "Invalid section header count: %d\n", ehdr.e_shnum);
        return;
    }

    // Allocate memory for section headers
    Elf64_Shdr *shdr = malloc(ehdr.e_shnum * sizeof(Elf64_Shdr));
    if (!shdr) {
        perror("Failed to allocate memory for section headers");
        return;
    }

    // Read section headers
    fseek(in_file, ehdr.e_shoff, SEEK_SET);
    fread(shdr, sizeof(Elf64_Shdr), ehdr.e_shnum, in_file);

    // Check if section name string table index is valid
    if (ehdr.e_shstrndx >= ehdr.e_shnum) {
        fprintf(stderr, "Invalid section header index for string table: %d\n", ehdr.e_shstrndx);
        free(shdr);
        return;
    }

    // Read the section name string table
    fseek(in_file, shdr[ehdr.e_shstrndx].sh_offset, SEEK_SET);
    if (shdr[ehdr.e_shstrndx].sh_offset >= file_size) {
        fprintf(stderr, "Invalid offset for section name string table: %zu\n", shdr[ehdr.e_shstrndx].sh_offset);
        free(shdr);
        return;
    }

    char *section_names = malloc(shdr[ehdr.e_shstrndx].sh_size);
    if (!section_names) {
        perror("Failed to allocate memory for section names");
        free(shdr);
        return;
    }

    fread(section_names, 1, shdr[ehdr.e_shstrndx].sh_size, in_file);

    // Now, you can process the section headers and identify the text section
    for (int i = 0; i < ehdr.e_shnum; i++) {
        char *sec_name = section_names + shdr[i].sh_name;
        if (shdr[i].sh_type == SHT_PROGBITS && strcmp(sec_name, ".text") == 0) {
            printf("Found .text section: Index = %d, Offset = %zu, Size = %zu\n", 
                    i, shdr[i].sh_offset, shdr[i].sh_size);
            // You can process this section here (e.g., read its contents, extract functions, etc.)
        }
    }

    // Clean up
    free(section_names);
    free(shdr);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }

    // Open the ELF file
    FILE *in_file = fopen(argv[1], "rb");
    if (!in_file) {
        perror("Failed to open ELF file");
        return 1;
    }

    // Get the file size
    fseek(in_file, 0, SEEK_END);
    size_t file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);

    // Read the sections from the ELF file
    read_text_section(in_file, file_size);

    // Close the ELF file
    fclose(in_file);

    return 0;
}