#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <zlib.h>

#define BUFFER_SIZE (8 * 1024)  // 8KB buffer
#define DEFAULT_WIDTH 60

void print_usage(const char *prog_name) {
    fprintf(stderr, "Wrap FASTA sequence lines to a specified width.\n\n");
    fprintf(stderr, "Usage: %s [options] <file.fasta(.gz)>\n\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -w, --width N    Line width (default: %d).\n", DEFAULT_WIDTH);
    fprintf(stderr, "  -0               No wrapping (one line per sequence)\n");
    fprintf(stderr, "  -h, --help       Show this help\n\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, "  %s -w 80 genome.fa.gz | gzip > genome_wrapped.fa.gz\n", prog_name);
}

gzFile open_input(const char *filename) {
    // If filename is NULL or "-", read from stdin
    if (!filename || strcmp(filename, "-") == 0) {
        return gzdopen(fileno(stdin), "rb");
    }

    // Check file existence
    if (access(filename, F_OK) != 0) {
        fprintf(stderr, "Error: file %s does not exist.\n", filename);
        return NULL;
    }

    // Check if file can be read (and exists)
    if (access(filename, R_OK) != 0) {
        fprintf(stderr, "Error: file %s is not readable.\n", filename);
        return NULL;
    }

    return gzopen(filename, "rb");
}

void wrap_fasta(gzFile fp, int width) {
    char buffer[BUFFER_SIZE];
    int column = 0;

    while (gzgets(fp, buffer, BUFFER_SIZE)) {
        
        if (buffer[0] == '>') {
            // Finish the previous fasta entry
            if (column != 0) {
                putchar_unlocked('\n');
                column = 0;
            }
            printf("%s", buffer);
            continue;
        }

        for (size_t i = 0; buffer[i] != '\0'; i++) {
            char c = buffer[i];
            // Skip newline characters from the input
            if (c == '\n' || c == '\r') continue;
            
            // Print the base 
            putchar_unlocked(c);
            column++;

            /*
            If wrapping is enabled (width > 0),
            insert a newline when the line is full.
            */
            if (width > 0 && column == width) {
                putchar_unlocked('\n');
                column = 0;
            }
        }
    }

    if (column != 0) putchar_unlocked('\n');
}

int main(int argc, char *argv[]) {

    setvbuf(stdout, NULL, _IOFBF, 1 << 20);  // 1 MB output buffer

    static struct option long_options[] = {
        {"width", required_argument, 0, 'w'},
        {"help",  no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int width = DEFAULT_WIDTH;
    int opt;
    while ((opt = getopt_long(argc, argv, "w:0h", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'w':
                char *end;
                width = strtol(optarg, &end, 10);
                if (*end != '\0' || width < 0) {
                    fprintf(stderr, "Error: Invalid width value.\n");
                    print_usage(argv[0]);
                    return 1;
                }
                break;
            case '0':
                width = 0;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    int fasta_count = argc - optind;
    if (fasta_count > 1) {
        fprintf(stderr, "Error: No support for multiple input files. Expected 1, got %d\n\n", fasta_count);
        print_usage(argv[0]);
        return 1;
    }

    char *fasta_file = NULL;
    if (optind < argc) {
        fasta_file = argv[optind];
    }

    gzFile fp = open_input(fasta_file);
    if (!fp) {
        fprintf(stderr, "Error: could not open input\n");
        return 1;
    }

    wrap_fasta(fp, width);

    gzclose(fp);
    return 0;
}