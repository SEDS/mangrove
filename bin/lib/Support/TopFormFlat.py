# ----------------------------------------
# topformflat.py
#
# Demonstrates how to grab arbitray C code enclosed by braces.
# It resolves nested braces
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
  ('charlit','exclusive'),
  ('hash','exclusive'),
)


def t_NEWLINE(t):
    r"\n"
    t.lexer.lineno += 1
    if t.lexer.level <= t.lexer.threshold:
        t.lexer.out.write(t.value)
        t.lexer.last_newline = t.lexer.lineno
        if t.lexer.last_found and t.lexer.lines:
            if len(t.lexer.lines[-1]) == 1 and t.lexer.lines[-1][-1] != t.lexer.lineno-1:
                t.lexer.lines[-1].append(t.lexer.lineno-1)
            elif len(t.lexer.lines[-1]) == 1 and t.lexer.lines[-1][-1] == t.lexer.lineno-1:
                del t.lexer.lines[-1]
                # t.lexer.lines.append([t.lexer.lineno-1])
                t.lexer.last_found = False
    # else:
        # t.lexer.lines[-1].append(t.lexer.lineno-1)


def t_QUOT(t):
    r'"'
    t.lexer.out.write(t.value)
    t.lexer.begin('string')

#TODO: string with new line... what should I do?
def t_string_NEWLINE(t):
    r"\n"
    t.lexer.lineno += 1
    if t.lexer.level <= t.lexer.threshold:
        t.lexer.out.write(t.value)
        t.lexer.last_newline = t.lexer.lineno

def t_string_ESCAPE(t):
    r'(?:\#|\\n|\\\*|\\")'
    t.lexer.out.write(t.value)

def t_string_END(t):
    r'"'
    t.lexer.out.write(t.value)
    t.lexer.begin("INITIAL")

def t_string_ELSE(t):
    r'[^\"\\\n]+'
    t.lexer.lineno += t.value.count('\n')
    t.lexer.out.write(t.value)

def t_string_error(t):
    r"."
    t.lexer.out.write(t.value[0])
    t.lexer.skip(1)

def t_TICK(t):
    r"'"
    t.lexer.out.write(t.value)
    t.lexer.begin('charlit')

def t_charlit_END(t):
    r"'"
    t.lexer.out.write(t.value)
    t.lexer.begin('INITIAL')

def t_charlit_ELSE(t):
    r'(?:\\n|.|\#)'
    t.lexer.out.write(t.value)

def t_charlit_error(t):
    r"."
    print("ERROR!!!")
    t.lexer.skip(1)


def t_HASH(t):
    r'\#'
    if t.lexer.last_newline != -1 and t.lexer.last_newline != t.lexer.lineno:
        t.lexer.out.write('\n')
        t.lexer.last_newline = t.lexer.lineno
        if t.lexer.lines and len(t.lexer.lines[-1]) == 1 and t.lexer.lines[-1][-1] != t.lexer.lineno-1:
            t.lexer.lines[-1].append(t.lexer.lineno-1)
    t.lexer.out.write(t.value)
    t.lexer.begin('hash')

def t_hash_NEWLINE(t):
    r"\n"
    t.lexer.out.write(t.value)
    t.lexer.lineno += 1
    t.lexer.last_newline = t.lexer.lineno
    if not t.lexer.last_found:
        if t.lexer.lines and len(t.lexer.lines[-1]) == 1:
            del t.lexer.lines[-1]
        t.lexer.lines.append([t.lexer.lineno])
    t.lexer.begin('INITIAL')

def t_hash_ELSE(t):
    r"."
    t.lexer.out.write(t.value)

def t_hash_error(t):
    r""
    print("ERROR!!! (imposible)")
    t.lexer.skip(1)

# Match the first {. Enter charlit state.
def t_RBRACE(t):
    r'\{'
    t.lexer.level += 1
    if t.lexer.level == t.lexer.threshold + 1:
        if not t.lexer.lines \
            or len(t.lexer.lines[-1]) > 1 and t.lexer.lines[-1][-1] != t.lexer.lineno:
            t.lexer.lines.append([t.lexer.lineno])
            t.lexer.last_found = False
    t.lexer.out.write(t.value)
    # TODO: Possible new line

def t_LBRACE(t):
    r"\};?" # TODO: check spaces in between
    t.lexer.level -= 1
    if t.lexer.level == t.lexer.threshold:
        t.lexer.last_found = True
    t.lexer.out.write(t.value)

def t_ELSE(t):
    r'[^\{\}\n\"\']+'
    t.lexer.out.write(t.value)

# Mandatory Error handling rule
def t_error(t):
    # print t.value[0],
    t.lexer.skip(1)



def print_help():
    msg = """\nScript to flatten and remove comments from a c-style program.
\nUsage: sys.argv[0] threshold input_file output_file
Where:
\t-threshold\t for the topformflat
\t-input_file\tfile to be read
\t-output_file\tresulting file
"""
    sys.stderr.write(msg)


def topformflat(threshold, input_file, output_file=None):
    """Flattens threshold levels the input file
    returns the first and last lines number (starting from 1) that have been compresed.
    Ex.: for
    1 if (true) {
    2   return 0
    3 }
    we return [[1,3]]
    """
    with open (input_file, "r") as myfile:
        data = myfile.read()

    if output_file:
        out = open(output_file, 'w')
    else:
        out = sys.stdout

    # create lexer
    lexer = lex.lex(reflags = re.IGNORECASE)
    # initialize the lexer
    lexer.out = out
    lexer.level = 0
    lexer.lines = []
    lexer.last_found = True
    lexer.threshold = threshold
    lexer.last_newline = -1
    # lexer.level = 0
    # if threshold == 0:
    #     lexer.exclude = []
        # lexer.begin('ccode')
    # Tokenize (case insensitive matches)
    lexer.input(data)
    for tok in lexer:
        pass
        # print "val =\t",tok.value
        # out.write(tok.type.rjust(24) + tok.value)
        # print "val =\t",tok.type, tok.value, tok.lineno, tok.lexpos
    if len(lexer.lines) > 0 and len(lexer.lines[-1]) < 2:
        if lexer.lineno == lexer.lines[-1][-1]:
            del lexer.lines[-1]
        else:
            lexer.lines[-1].append(lexer.lineno)

    if output_file:
        out.close()

    return  lexer.lines


if __name__ == "__main__":
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print_help()
        sys.exit(1)

    threshold = int(sys.argv[1])
    if len(sys.argv) == 4:
        out = sys.argv[3]
    else:
        out = None
    res = topformflat(threshold, sys.argv[2], out)
    if out:
        with open (out, "a") as myfile:
            myfile.write(repr(res))
    else:
        sys.stdout.write(repr(res))
