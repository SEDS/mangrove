# ----------------------------------------
# comments_remover.py
#
# Remmoves c-style comments and empty lines
# from a given program
# ----------------------------------------

# Import
import sys
import ply.lex as lex
import re

tokens = (
    'COMMENT',
)

# Declare the state
states = (
  ('comment','exclusive'),
  ('line','exclusive'),
  ('string','exclusive'),
  ('char','exclusive'),
)


def t_QUOT(t):
    r'"'
    print_val(t, t.value)
    t.lexer.begin("string")

def t_string_NOQUOT(t):
    r'\\"'
    print_val(t, t.value)

def t_string_QUOT(t):
    r'"'
    print_val(t, t.value)
    t.lexer.begin("INITIAL")

def t_string_NEWLINE(t):
    r'\n'
    t.lexer.lineno += 1
    print_val(t, t.value)

def t_string_SCAPEDLINE(t):
    r'(:?\\n|\*)'
    print_val(t, t.value)

def t_string_ELSE(t):
    r'[^"\*\\\n]+'
    print_val(t, t.value)

def t_string_error(t):
    r'.'
    print_val(t, t.value[0])
    t.lexer.skip(1)

def t_TICK(t):
    r"\'"
    print_val(t, t.value)
    t.lexer.begin('char')

def t_char_TICK(t):
    r"'"
    print_val(t, t.value)
    t.lexer.begin('INITIAL')

def t_char_error(t):
    r"."
    print_val(t, t.value[0])
    t.lexer.skip(1)

def t_SINGLELINE(t):
    r'\s*//'
    t.lexer.lineno += t.value.count('\n')
    #print "SINGLELINE",
    t.lexer.begin("line")

def t_line_NEWLINE(t):
    r'.*\n'
    t.lexer.lineno += 1
    if t.lexer.last_printed != '\n': # it's not a whitespace
        # print "t_line_NEWLINE =", repr(t.lexer.last_printed)
        print_val(t, '\n')
    t.lexer.begin("INITIAL")

def t_line_error(t):
    r'.'
    t.lexer.skip(1)

def t_MULTILINE(t):
    r"\s*/\*"
    t.lexer.lineno += t.value.count('\n')
    # print t.lexer.lexpos, t.value
    if not t.lexer.first_printed and not re.match(r'\s', t.lexer.last_printed):
        t.lexer.add_space =  True
    else:
        t.lexer.add_space =  False
    t.lexer.begin("comment")

def t_comment_NOEND(t):
    r"\\\*/"
    # print "t_comment_NOEND =", t.lexer.lineno, repr(t.value)

def t_comment_END(t):
    r"\*\/"
    if t.lexer.add_space:
        t.lexer.remaining_to_print = ' '
    t.lexer.begin("INITIAL")

def t_comment_NEWLINE(t):
    r"\n"
    # print "t_comment_NEWLINE =", t.lexer.lineno, repr(t.value)
    t.lexer.lineno += 1

def t_comment_ELSE(t):
    r"[^\*/\\\n]+"
    # print "t_comment_ELSE =", t.lexer.lineno, repr(t.value)
    # print "STRING ELSE =", repr(t.value)

def t_comment_error(t):
    r"."
    # print "t_comment_ERROR =", t.lexer.lineno, repr(t.value[0])
    # print "COMMENT ERROR =", repr(t.value[0])
    t.lexer.skip(1)

def t_NEWLINE(t):
    r"\s*\n"
    t.lexer.lineno += t.value.count('\n')
    # print "t_NEWLINE =", repr(t.value), t.lexer.lineno
    if t.lexer.last_printed != '\n': # it's not a whitespace
        print_val(t, '\n')

def t_ELSE(t):
    r"[^/\"]"
    print_val(t, t.value)

# Mandatory Error handling rule
def t_error(t):
    # TODO: this should be useless
    if t.value[0] == '\n':
        t.lexer.lineno += 1
    print_val(t, t.value[0])
    # print "t_error =", t.value[0]
    t.lexer.skip(1)


def print_val(t, value):
    lineno = t.lexer.lineno - value.count('\n')
    for line in range(lineno, t.lexer.lineno + 1):
        if not t.lexer.added_lines or (t.lexer.added_lines[-1] != line and value != '\n'):
            t.lexer.added_lines.append(line)
    if t.lexer.remaining_to_print and not re.match('\s', value[0]):
        t.lexer.out.write(t.lexer.remaining_to_print + value)
        t.lexer.remaining_to_print = ""
    else:
        if re.match('\s', value[0]): t.lexer.remaining_to_print = ""
        t.lexer.out.write(value)
    # lexer.out.write(value)
    t.lexer.first_printed = False
    t.lexer.last_printed = value[-1]


def print_help():
    msg = """\nScript to remove comments from a c-style program.
\nUsage: sys.argv[0] input_file [output_file]
Where:
\t-input_file\tfile to be read
\t-output_file (optional)\tresulting file
"""
    sys.stderr.write(msg)


def remove_comments(input_file, output_file=None):
    with open (input_file, "r") as myfile:
        data = myfile.read()

    if output_file:
        out = open(output_file, 'w')
    else:
        out = sys.stdout

    # create lexer
    lexer = lex.lex(reflags = re.IGNORECASE)
    lexer.out = out
    lexer.last_printed = '\n'
    lexer.first_printed = True
    lexer.added_lines = []
    lexer.remaining_to_print = ''
    # Tokenize (case insensitive matches)
    lexer.input(data)
    for tok in lexer:
        pass
        # print "val =\t",tok.value
        # out.write(tok.type.rjust(24) + tok.value)
        # print "val =\t",tok.type, tok.value, tok.lineno, tok.lexpos
    if lexer.last_printed != '\n': # it's not a whitespace
        # print "t_line_NEWLINE =", repr(t.lexer.last_printed)
        lexer.out.write('\n')

    if output_file:
        out.close()

    return lexer.added_lines


if __name__ == "__main__":
    if len(sys.argv) < 2 and len(sys.argv) > 3:
        print_help()
        sys.exit(1)

    if len(sys.argv) == 3:
        out = sys.argv[2]
    else:
        out = None
    res = remove_comments(sys.argv[1], out)
    if out:
        with open (out, "a") as myfile:
            myfile.write(repr(res))
    else:
        sys.stdout.write(repr(res))
