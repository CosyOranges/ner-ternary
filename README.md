[![CMake Build Matrix](https://github.com/CosyOranges/ner-ternary/actions/workflows/cicd.yml/badge.svg)](https://github.com/CosyOranges/ner-ternary/actions/workflows/cicd.yml)
# ner-ternary
## What is it?
ner-ternary is a command line tool that will annotate a directory of documents with key terms provided in a `.tsv` file or (for smaller tasks) supplied through the command.

The end result is a directory of `.json` files with the following annotation structure:
```json
{
    "Annotations": {
        "key1": {
            "line": {
                "x": [
                        [start1_char_pos, end1_char_pos],
                        [start2_char_pos, end2_char_pos]
                    ],
                "y": {},
                .
                .
                .
            },
        "key2": {
            "line": {
                "x": {},
                "y": {},
                .
                .
                .
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
