This page contains development related documentation for the SIM-VICUS project.

User docs are found on the webpage: https://sim-vicus.de

## Developer documentation

The following documentation is automatically generated with Asciidoctor. 

- [NANDRAD-CodeGenerator](NANDRAD-CodeGenerator/index.html)
- [NANDRAD-Model and Implementation Docs](NANDRAD-Model-Reference/index.html)
- [Developer Information](Developer-Documentation/index.html)

The input `adoc`-files for above documentation are in the `doc` directory. 
You can update the documentation by running the `build.sh` script.
Also check for correct references by running the `linkcheck.sh` script.

*WARNING:* Do not modify the generated documentation in the `docs` directory, as
all changes there will be lost when the documentation is updated next.

*NOTE:* avoid committing updated PDF documentation to the gitrepo, as these
binary files have to be stored entirely (no diff possible) and would quickly 
cause the git repo size to explode.

## Library Reference

This is the programming library reference (currently only for the NANDRAD data 
model library), generated with Doxygen. It can be updated by running doxygen
in the libraries `doc` directory.  

- [NANDRAD-Library API Documentation](api/NANDRAD-API)

(If you miss information in the API docs, feel free to add that directly in the source code).
