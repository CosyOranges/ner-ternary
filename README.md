[![CMake Build Matrix](https://github.com/CosyOranges/ner-ternary/actions/workflows/cicd.yml/badge.svg)](https://github.com/CosyOranges/ner-ternary/actions/workflows/cicd.yml)
# ner-ternary
## What is it?
ner-ternary is a command line tool that will annotate a directory of documents with key terms provided in a `.tsv` file or (for smaller tasks) supplied through the command.

The end result is a directory of `.json` files with the following annotation structure:
```json
{
    "Annotations": {
        "phrases": {
            ...
        },
        "tokens": {
            "key1": {
                "line": {
                    "x": [
                            [start1_char_pos, end1_char_pos],
                            [start2_char_pos, end2_char_pos]
                        ],
                    "y": [
                        [..., ...]
                    ],
                    .
                    .
                    .
                },
            "key2": {
                "line": {
                    "x": [
                        [..., ...]
                    ],
                    "y": [
                        [..., ...]
                    ],
                    .
                    .
                    .
                }
            }
            }
        }
    }
}

```

A basic example of the type of file structure this tool is aimed at would be:
```
root/
    key_words.tsv
    Documents/
        doc1.txt
        doc2.txt
        doc3.txt
        .
        .
        .
    out/
```

## Clean Any Data
If you have a `.tsv` where your key words are located then you can extract those from the tsv using the `clean-tsv` command.
- **Command**: `clean-tsv`
    - **Options**:
        - `-s`: This is a flag to shuffle the `outfile.txt`, if ommitted then the words will be written to the `outfile.txt` in alphabetical order.
        - `-c <x>`: This flag is **required** and it is to tell the program which column in the `.tsv` you wish to extract.
        - The remaining options are the path to the input `.tsv` and the path to where you want the `outfile.txt` written.
```
nerternary clean-tsv -s -c <x> <path/to/input.tsv> <path/to/outfile.txt>
```

## Annotation
After cleaning data (or if you already have a `.txt` file with your desired words on a new line), the `annotate` command can be used.
- **Command**: `annotate`
    - **Options**:
        - `-p`: This is a flag to switch on parallel processing, the input `.txt` files will be split up over the desired number of processors.
        - `-t`: The number of threads/processors to use. Please check your systems capabilities before attempting to overprescribe processors.
        - `-w <"list, of, words">`: **NOT IMPLEMENTED** Supply a list of words via the command line to annotate for
        - The remaining options are the `.txt` file of words/phrases to be annotated for, the path to the `input/dir` containing the `.txt` files to annotate, and the `output/dir` where an `annotations/` sub directory will be created and the `.json` annotations will be written.

- **FUTURE:** You will also be able to supply a list of words via the command line to annotate for.

## Limitations
Currently this CLI only supports annotating for single or hyphenated words owing to a lack of noun phrase building post tokenization.
