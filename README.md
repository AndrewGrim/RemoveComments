# RemoveComments

## Remove C style comments from file

Takes two arguments:

    -input "path"

The path to the input file from which to remove comments.

    -output "path"

The path to which the new file with the comments removed will be created.

***NOTE***

The -input, -output arguments can be given in any order.

While the comments are removed, the file structure remains mostly the same.

Single line comments are replaced with an empty line.

The entire multi line comment is replaced by an empty line.

### Example

    ./RemoveComments.exe -input c:/fake/path/main.c -output /home/user/modified-main.txt
