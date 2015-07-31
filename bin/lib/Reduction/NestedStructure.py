import sys
import os

import clang.cindex


FILTER_TYPES = [clang.cindex.CursorKind.FUNCTION_DECL, # DONE
                clang.cindex.CursorKind.NAMESPACE,
                clang.cindex.CursorKind.IF_STMT,
                clang.cindex.CursorKind.SWITCH_STMT,
                clang.cindex.CursorKind.CASE_STMT,
                clang.cindex.CursorKind.DEFAULT_STMT,
                clang.cindex.CursorKind.CLASS_DECL,
                clang.cindex.CursorKind.CXX_METHOD,
                ]

MAX_WIDTH = 200

# TODO: this is for mac
# clang.cindex.Config.set_library_path("/Library/Developer/CommandLineTools/usr/lib")


class NestedError(Exception):
    """Exception raised for errors while creating the snippets.

    Arguments:
    msg  -- explanation of the error
    """

    def __init__(self, msg):
        self.msg = msg


def is_node_type_useful(node):
    return node.kind in FILTER_TYPES


def remove_dup(x):
    if x == []:
        return []
    else:
        return [x[i] for i in range(len(x)-1) if x[i] != x[i+1]] + [x[-1]]


def find_first(tokens, spell):
    pos = 0
    while tokens[pos].spelling != spell:
        pos += 1
    return pos


def find_last(tokens, spell):
    pos = - 1
    while tokens[pos].spelling != spell:
        pos -= 1
    return pos


def get_if_lines(node):
    """ Gets the lines of the if (...) { } else { }. For example, for the code:
1. if (var == 
2.      1) 
3.  {
4.
5.  } else 
6.  {
7.
8.  }

Will return [[1,2,3,5,6,8]]
    """
    fst = node.location.line
    children = list(node.get_children())
    
    condition = children[0]
    tokens = list(condition.get_tokens())
    snd = tokens[-1].location.line 
    
    then = children[1]
    tokens = list(then.get_tokens())
    if tokens[0].spelling == '{':
        snd = tokens[0].location.line
        res = range(fst, snd + 1)
        pos = find_last(tokens, '}')
        res.append(tokens[pos].location.line)
    else: 
        res = range(fst, snd + 1)

    if len(children) == 3:
        res.append(tokens[-1].location.line) # the else
        else_node = children[2]
        tokens = list(else_node.get_tokens())
        if tokens[0].spelling == '{':
            res.append(tokens[0].location.line)
            pos = find_last(tokens, '}')
            res.append(tokens[pos].location.line)
        elif tokens[0].spelling == 'if':
            res.extend(get_if_lines(else_node))

    return remove_dup(res)


def process_if_node(node, location):
    lines = get_if_lines(node)
    if location.line >= lines[0] and location.line <= lines[-1]:
        return lines
    else:
        return []


def process_func_decl(node, location):
    child = next(node.get_children())
    tokens = list(child.get_tokens())
    if tokens[0].spelling == '{':
        res = range(node.location.line, tokens[0].location.line + 1)
        pos = find_last(tokens, '}')
        res.append(tokens[pos].location.line)
    else:
        res = [node.location.line]

    if location.line >= res[0] and location.line <= res[-1]:
        return remove_dup(res)
    else:
        return []


def process_switch_node(node, location):
    [condition, inner] = list(node.get_children())
    tokens = list(condition.get_tokens())
    res = range(node.location.line, tokens[-1].location.line + 1)
    inner_tokens = list(inner.get_tokens())
    if inner_tokens[0].spelling == '{':
        res.append(inner_tokens[0].location.line)
        pos = find_last(inner_tokens, '}')
        res.append(inner_tokens[pos].location.line)
    for child in inner.get_children():
        if child.kind == clang.cindex.CursorKind.CASE_STMT:
            tokens = next(child.get_children()).get_tokens()
            tokens = list(tokens)
            res.extend(range(child.location.line, tokens[-1].location.line + 1))
        elif child.kind == clang.cindex.CursorKind.BREAK_STMT:
            res.append(child.location.line)
        elif child.kind == clang.cindex.CursorKind.DEFAULT_STMT:
            tokens = list(child.get_tokens())
            pos = find_first(tokens, ':')
            res.extend(range(child.location.line, tokens[pos].location.line + 1))

    res = remove_dup(res)
    res.sort()
    if location.line >= res[0] and location.line <= res[-1]:
        return res
    else:
        return []


def get_node_in_line(translation_unit, fd, line_num):
    col = 1
    found = False
    while not found and col < MAX_WIDTH:
        location = clang.cindex.SourceLocation.from_position(translation_unit, \
                                                             fd, line_num, col)
        node = translation_unit.cursor.from_location(translation_unit, location)
        if node.location.line < line_num:
            col += 1
        else:
            found = True
    if col == MAX_WIDTH:
        raise NestedError('Unable to find node in line [%i]' % line_num)
    return (node, location)


def find_nested_structure_helper(node, location, history):
    if node.location.file and node.location.file.name != location.file.name:
        return False
    if node.location.line > location.line:
        return False
    if node.location.line == location.line:
        if is_node_type_useful(node):
            history.append(node.location.line)
        return True

    for c in node.get_children():
        if find_nested_structure_helper(c, location, history):
            if is_node_type_useful(node):
                if node.kind == clang.cindex.CursorKind.IF_STMT:
                    lines = process_if_node(node, location)
                    history.extend(lines)
                elif node.kind == clang.cindex.CursorKind.FUNCTION_DECL or \
                     node.kind == clang.cindex.CursorKind.NAMESPACE:
                    lines = process_func_decl(node, location)
                    history.extend(lines)
                elif node.kind == clang.cindex.CursorKind.SWITCH_STMT:
                    lines = process_switch_node(node, location)
                    history.extend(lines)
                else:
                    history.append(node.location.line)
            return True

    return False

def find_nested_structure(node, locations):
    res = []
    for location in locations:
        history = []
        find_nested_structure_helper(node, location, history)
        history = list(set(history))
        history.sort()
        res.extend(history)
    res = list(set(res))
    res.sort()
    return res


def find_nested_lines(fname, compilation_args, line_nums, lines_forced=False):
    # TODO: check for errors
    index = clang.cindex.Index(clang.cindex.conf.lib.clang_createIndex(False, True))
    # index = clang.cindex.Index.create()
    compilation_args.append('-stdlib=libstdc++')
    translation_unit = index.parse(fname, compilation_args)
    f = clang.cindex.File.from_name(translation_unit, translation_unit.spelling)
    locations = []
    if not lines_forced:
        for line_num in line_nums:
            (_, location) = get_node_in_line(translation_unit, f, line_num)
            locations.append(location)
    else:
        for line_num in line_nums:
            try:
                (_, location) = get_node_in_line(translation_unit, f, line_num)
                locations.append(location)
            except NestedError:
                pass
    lines = find_nested_structure(translation_unit.cursor, locations)
    # TODO: in case that it cannot compile the file
    if not lines:
        lines = line_nums
    return lines


# example: python NestedStructure.py ../../../../../mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcases/CWE476_NULL_Pointer_Dereference/CWE476_NULL_Pointer_Dereference__wchar_t_72a.cpp "-I ../../../../../mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcasesupport/" 41
if __name__ == "__main__":
    fname = sys.argv[1]
    args = sys.argv[2].split()
    line_nums = [int(sys.argv[3])]
    lines = find_nested_lines(fname, args, line_nums)
    print lines
