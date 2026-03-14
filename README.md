# Bioutils

A personal collection of standalone, portable command-line utilities for bioinformatics and data analysis.

## Categories

- **`fasta/`** - Scripts working with FASTA sequence files
- **`fastq/`** - Scripts working with FASTQ files
- **`file_formats/`** - Scripts modifying or converting file formats

More information on each script given in the README file in each folder.

---

## Installation

### **Option 1: Install all scripts**

Clone the repository and run the installer:

```bash
git clone https://github.com/sverwimp/portable-bioinformatics-scripts.git
cd portable-bioinformatics-scripts
chmod +x install.sh
./install.sh
```

This will:
- Install all scripts to `~/.bioutils` (or a custom directory of your choice)
- Make all scripts executable
- Compile any C programs automatically (only if gcc and zlib are present)
- Add the directory to your PATH

**Custom installation directory:**
```bash
./install.sh                    # Install to ~/.bioutils
./install.sh ~/myscripts        # Install to ~/myscripts
./install.sh /usr/local/bin     # System-wide (requires sudo)
```

Use `./install.sh -h` for more information

### **Option 2: Use individual scripts**

Each script is self-contained. You can copy any single script directly and use it without installing the entire collection. 

Scripts written in C can be compiled as followed:
`gcc -O2 <scriptname>.c -o <scriptname> -lz`

---

## Management

Once installed, use the `bioutils` command to manage the collection of scripts.

### Usage

`bioutils <subcommand>`

| Subcommand         | Description                                                          |
| ------------------ | -------------------------------------------------------------------- |
| `list`             | List all available scripts in your installation directory.           |
| `info <name>`      | Show metadata (path, executable status, modified date) for a script. |
| `update`           | Automatically pull the latest changes from GitHub and reinstall.     |
| `remove <name...>` | Remove specific script(s) by name.                                   |
| `uninstall-all`    | Remove all scripts, the directory, and clean up your shell's `PATH`. |


### Updating

Use the `bioutils` update subcommand to automatically clone the repository to a temporary location, run the install script again (keeping current install directory in mind), and remove the local repository.

Or pull new changes manually and simply run the installer again:
```bash
git pull
./install.sh <installation_directory>
```

Only modified or new scripts will be copied. Use `./install.sh -f` to force reinstall everything.

---

## Requirements

All scripts use either standard Unix tools (bash, awk, grep), Python, or C (requires gcc and zlib) and should work on Linux/macOS without additional dependencies.
