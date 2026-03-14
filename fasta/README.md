# FASTA Tools

Command-line utilities for working with FASTA files.

## Scripts

Overview:
- [fasta-extract](#fasta-extract)
- [fasta-size](#fasta-size)
- [fasta-split](#fasta-split)
- [fasta-stats](#fasta-stats)
- [fasta-wrap](#fasta-wrap)

---

### `fasta-extract`
Extract fasta records from FASTA files through pattern matching on headers.

```bash
# Basic substring search
fasta-extract 'PilB' genome.faa

# Case-insensitive with regex
fasta-extract -i -r '^chr[0-9]+' genome.fa

# Extract multiple patterns from a file
fasta-extract -l ids.txt genome.faa

# Count matches only
fasta-extract -c 'mitochondria' genome.fa

# Working with gzipped data
zcat genome.fa | fasta-extract 'search-term'
```

**Options:** `-i` (case-insensitive), `-r` (regex), `-x` (exact ID), `-l` (list file), `-v` (invert), `-n` (names only), `-c` (count), `-m` (max number of matches to report)

Use `fasta-extract -h` for help.

> [!TIP]
> If you only have a few patterns, you don't need a list file. Use the regex pipe `|` to match multiple items:
> 
> ```bash
> fasta-extract -r '(chr1|chrX|chrY)' genome.fa
> fasta-extract -r 'contig_[0-9]+' genome.fa
> ```

---

### `fasta-size`
Calculate total sequence length or extract/filter FASTA entries by size.

```bash
# Single file (prints size only)
fasta-size genome.fa
# Output: 3141592

# Multiple files (prints filename: size)
fasta-size genome1.fa genome2.fa
# Output: genome1.fa: 3141592
#         genome2.fa: 2718281

# From stdin
cat genome.fa | fasta-size

# Extract smallest entry
fasta-size --min genome.fa

# Extract largest entry
fasta-size --max genome.fa

# Extract and save entries >= 1000 bp
fasta-size --threshold 1000 genome.fa --out large_entries.fa

# Extract entries <= 500 bp
fasta-size --max-threshold 500 genome.fa
```

**Options:** `--min` (smallest entry), `--max` (largest entry), `--threshold SIZE` (entries ≥ SIZE), `--max-threshold SIZE` (entries ≤ SIZE), `-o` (output file), `-w` (line width)

---

### `fasta-split`
Split FASTA files by sequence count, parts, or size.

```bash
# Split every 100 sequences
fasta-split -n 100 genome.fa
# Output: genome_001.fa, genome_002.fa, ...

# Split into 4 equal parts
fasta-split -p 4 genome.fa
# Output: genome_part1.fa, genome_part2.fa, genome_part3.fa, genome_part4.fa
```

*Splitting modes (choose one):**
- `-n N` (split every N sequences)
- `-p P` (split into P equal parts)
- `-s` (one file per sequence, named by sequence ID)
- `-b SIZE` (split by file size: e.g., '100MB', '1.5GB', '500KB')

**Options:** `-o DIR` (output directory, default: current), `-w N` (line width, default: 60), `--force` (overwrite existing files)

---

### `fasta-stats`
Calculate comprehensive statistics for FASTA files.

```bash
# Single file (human-readable output)
fasta-stats genome.fa

# Multiple files (automatic TSV format)
fasta-stats *.fa

# Include nucleotide/amino acid composition
fasta-stats --composition genome.fa

# Include gap and N-count statistics
fasta-stats --gaps genome.fa

# Output as JSON
fasta-stats genome.fa --json

# Multiple files to CSV
fasta-stats *.fa --csv > stats.csv

# All statistics with composition and gaps
fasta-stats --composition --gaps genome.fa
```

**Default Statistics:**
- Sequence type (auto-detected: nucleotide/protein/mixed; checks only first 10 fasta entries)
- Number of sequences
- Total, mean, median, min, max lengths
- Standard deviation
- N50 (nucleotides only)
- GC content (nucleotides only)

> [!NOTE]
> Single file input produces human-readable text output. Multiple files automatically switch to tabular (TSV) format unless a specific format is specified.

Can process multiple files from `find` using `xargs`: `find . -name "*.fa" | xargs fasta-stats`

---

### `fasta-wrap`

Wrap or unwrap FASTA sequence lines to a specified width.

```bash
# Default 60 character wrapping
fasta-wrap genome.fa(.gz)

# Custom width (80 characters)
fasta-wrap -w 80 genome.fa

# Unwrap sequences to single lines
fasta-wrap -0 genome.fa

# From stdin
cat genome.fa | fasta-wrap -w 80 | gzip > genome_wrapped.fa.gz
```

## Notes

All scripts:
- Accept input from files or stdin
- Include `-h` flag for help documentation