## Tree-Cli <a name="treecli"></a>

### Annotation <a name="annotation"></a>
After cleaning data (or if you already have a `.txt` file with your desired words on a new line), the `annotate` command can be used.
- **Command**: `annotate`
    - **Options**:
        - `-p`: This is a flag to switch on parallel processing, the input `.txt` files will be split up over the desired number of processors.
        - `-t`: The number of threads/processors to use. Please check your systems capabilities before attempting to overprescribe processors.
        - `-w <"list, of, words">`: **NOT IMPLEMENTED** Supply a list of words via the command line to annotate for
        - The remaining options are the `.txt` file of words/phrases to be annotated for, the path to the `input/dir` containing the `.txt` files to annotate, and the `output/dir` where an `annotations/` sub directory will be created and the `.json` annotations will be written.

- **FUTURE:** You will also be able to supply a list of words via the command line to annotate for.
