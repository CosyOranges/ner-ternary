# ner-ternary
## What is it?
ner-ternary is a command line tool that will annotate a directory of documents with key terms provided in a `.tsv` file.

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

The tool can then be called with the following command line options:
```
-d <relative_path_to_tsv_file>
-i <relative_path_to_txt_files>
-o <relative_path_to_desired_output_dir>
```

### Example call for the above File Structure:
```bash
./ner-ternary -d ./key_words.tsv -i ./Documents -o ./out
```

This would then create the `./out` directory and populate it with:
```
root/
    out/
        annotations/
            doc1.json
            doc2.json
            doc3.json
            .
            .
            .
        keywords.txt (The Keywords extracted from the .txt file used to build the ternary tree)
```
