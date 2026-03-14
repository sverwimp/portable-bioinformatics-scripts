# File Formats

Utilities to modify or convert file formats used in bioinformatics.

## Scripts

### `gbk2fasta`
Convert GenBank files to FASTA format.

By default, outputs nucleotide sequences. Use the `--protein` flag to extract amino acid sequences from CDS features (requires translation attributes; pseudogenes are skipped).

```bash
gbk2fasta genome.gbk(.gz|bz2) --out genome.fna        # Nucleotide output
gbk2fasta --protein genome.gbk --out genome.faa       # Amino acid output

# Without --out, the output will print to the standard output
gbk2fasta genome.gbk.gz | gzip > genome.fna.gz        # Compressed I/O
```
---

### `prokkify`
Create a Prokka-like GFF3 file with embedded FASTA sequence(s) from common genome annotation formats.

Coverts either a **Genbank** file or a combination of a **GFF3 and FASTA** file into a single GFF3 file containing a `##FASTA` section, suitable for downstream tools that expect Prokka-style input.

```bash
prokkify --genbank genome.gbk(.gz|bz2) --out genome.gff
prokkify --gff annotations.gff --fasta genome.fna --out genome.gff

# Without --out, the output will print to the standard output
prokkify --genbank genome.gbk.gz | gzip > genome.gff.gz
```