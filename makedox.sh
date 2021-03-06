#!	/bin/sh

DOXYFILE=default.doxycfg

doxygen -s -g - | sed '
# special options for our docs

/ALWAYS_DETAILED_SEC/s/NO/YES/
/EXTRACT_ALL/s/NO/YES/
# /FILE_PATTERNS/s/$/*.c *.h/
/GENERATE_MAN/s/NO/YES/
/GENERATE_TREEVIEW/s/NO/YES/
/ INPUT /s/$/__MAGIC_INPUT__/
/OPTIMIZE_OUTPUT_FOR_C/s/NO/YES/
/OUTPUT_DIRECTORY/s/$/"__MAGIC_OUTPUT_DIRECTORY__"/
/PROJECT_NAME/s/$/"__MAGIC_PROJECT_NAME__"/
/SHOW_DIRECTORIES/s/NO/YES/

/DETAILS_AT_TOP/d
/FULL_PATH_NAMES/d
/MAX_DOT_GRAPH_HEIGHT/d
/MAX_DOT_GRAPH_WIDTH/d
/QUIET/d
/USE_WINDOWS_ENCODING/d

$a \
FULL_PATH_NAMES        = NO  \
QUIET = YES
' > $DOXYFILE
