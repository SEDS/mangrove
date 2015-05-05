# ----------------------------------------
# topformflat.py
#
# Demonstrates how to grab arbitray C code enclosed by braces.
# It.lexer.resolves nested braces
# and ignores braces in comments ( /* */ , //)
# and strings (" ",' ')
# ----------------------------------------

# Import
import sys
import ply.lex as lex
import re

tokens = (
    'STRING',
    # 'CHARLIT',
)

# Declare the state
states = (
    ('string','exclusive'),
    ('hash','exclusive'),
)


def t_NEWLINE(t):
    r"\n"
    t.lexer.res[t.lexer.lineno] = t.lexer.current_func
    t.lexer.lineno += 1

def t_QUOT(t):
    r'"'
    t.lexer.begin('string')

#TODO: string with new line... what should I do?
def t_string_NEWLINE(t):
    r"\n"
    t.lexer.res[t.lexer.lineno] = t.lexer.current_func
    t.lexer.lineno += 1

def t_string_ESCAPE(t):
    r'\\"'

def t_string_END(t):
    r'"'
    t.lexer.begin("INITIAL")

def t_string_ELSE(t):
    r'[^\"\n]+'

def t_string_error(t):
    r"."
    t.lexer.skip(1)

def t_HASH2(t):
    r'//.*'

def t_HASH(t):
    r'/\*'
    t.lexer.begin('hash')

def t_hash_NEWLINE(t):
    r"\n"
    t.lexer.res[t.lexer.lineno] = t.lexer.current_func
    t.lexer.lineno += 1

def t_hash_END(t):
    r"\*/"
    t.lexer.begin("INITIAL")

def t_hash_ELSE(t):
    r"[^*]"

def t_hash_error(t):
    r""
    t.lexer.skip(1)

# Match the first {. Enter charlit state.
def t_FUNC(t):
    r'void\s+(?:CWE.+|.*good.*|.*bad.*)\s*\(\s*\)\s*\{'
    t.lexer.last_found = t.lexer.blocks_found
    t.lexer.blocks_found += 1
    m = re.match(r'void\s+((?:CWE.+|.*good.*|.*bad.*))\s*\(\s*\)', t.value)
    t.lexer.current_func = m.groups()[0]
    for i in range(t.lexer.lineno, t.lexer.lineno + t.value.count('\n')):
        t.lexer.res[i] = t.lexer.current_func
    t.lexer.lineno += t.value.count('\n')

def t_LBRACE(t):
    r'\{'
    t.lexer.blocks_found += 1

def t_RBRACE(t):
    r'\}'
    t.lexer.blocks_found -= 1
    if t.lexer.blocks_found == t.lexer.last_found:
        t.lexer.current_func = ""

def t_ELSE(t):
    r'[^\{\}\n\"\'v]+'

# Mandatory Error handling rule
def t_error(t):
    # print t.value[0],
    t.lexer.skip(1)



def print_help():
    msg = """\nScript to get the function name from a line number in Juliet.
\nUsage: %s input_file
Where:
\t-input_file\tfile to be read
""" % sys.argv[0]
    sys.stderr.write(msg)


def lineno2fun(input_file):
    """
    Flattens t.lexer.reshold levels the input file
    returns the first and last lines number (starting from 1) that have been compresed.
    Ex.: for
    1 if (true) {
    2   return 0
    3 }
    we return [[1,3]]
    """
    with open (input_file, "r") as myfile:
        data = myfile.read()

    # create lexer
    lexer = lex.lex(reflags = re.IGNORECASE)
    # initialize the lexer
    lexer.blocks_found = 0
    lexer.last_found = 0
    lexer.current_func = ""
    lexer.res = {}
    # Tokenize (case insensitive matches)
    lexer.input(data)
    for tok in lexer:
        pass

    return  lexer.res


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print_help()
        sys.exit(1)

    res = lineno2fun(sys.argv[1])
    print(res)