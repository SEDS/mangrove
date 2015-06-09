import sys
import os

import clang.cindex


FILTER_TYPES = [clang.cindex.CursorKind.FUNCTION_DECL, 
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
clang.cindex.Config.set_library_path("/Library/Developer/CommandLineTools/usr/lib")


class NestedError(Exception):
    """Exception raised for errors while creating the snippets.

    Arguments:
    msg  -- explanation of the error
    """

    def __init__(self, msg):
        self.msg = msg


def is_node_type_useful(node):
    return node.kind in FILTER_TYPES


def find_semantic_parents(node):
    if node.kind == node.kind.TRANSLATION_UNIT:
        return []
    elif node.kind == clang.cindex.CursorKind.FUNCTION_DECL or \
            node.kind == clang.cindex.CursorKind.NAMESPACE:
        return find_semantic_parents(node.semantic_parent) + [node.location.line]
    # TODO: node.kind == CursorKind.CONDITIONAL_OPERATOR
    # TODO: CursorKind.SWITCH_STMT
    # TODO: CursorKind.GOTO_STMT
    else:
        return find_semantic_parents(node.semantic_parent)

def find_elsestmt(nodeIN):
    elseifbeginlineArrayIN = []
    elsebeginlineIN = None
    ifstructurenodeArrayIN = []
    ifstructureelseifnodeArrayIN = []
    #add then{} node
    for d in nodeIN.get_children():
        if (d.kind.name == 'COMPOUND_STMT'):
            ifstructurenodeArrayIN.append(d)
            break

    def find_elsestmtRE(nodeIN2):
        for e in nodeIN2.get_children():
            if e.kind.name == 'IF_STMT':
                #add elseif() node
                ifstructureelseifnodeArrayIN.append(e)
                find_elsestmtRE.node_lastelseifstmt = e
                elseifbeginlineArrayIN.append(e.extent.start.line)
                #add compound statement corresponding to elseif() node
                for f in e.get_children():
                    if (f.kind.name == 'COMPOUND_STMT'):
                        ifstructurenodeArrayIN.append(f)
                        break
                find_elsestmtRE(e)

    find_elsestmtRE.node_lastelseifstmt = nodeIN
    find_elsestmtRE(nodeIN)

    counter = 0
    for f in find_elsestmtRE.node_lastelseifstmt.get_children():
        if f.kind.name == 'COMPOUND_STMT':
            counter += 1
            if counter == 2:
                elsebeginlineIN = f.extent.start.line
                #add else() node
                ifstructurenodeArrayIN.append(f)

    return (elseifbeginlineArrayIN, elsebeginlineIN, \
            ifstructurenodeArrayIN, ifstructureelseifnodeArrayIN)



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
            if node.kind == clang.cindex.CursorKind.IF_STMT:
                _, _, if_elses, _ = find_elsestmt(node)
                if_elses.revert()
                for if_else in if_elses:
                    if if_else.location.line <= node.location.line:
                        history.append(if_else.location.line)
            else:
                history.append(node.location.line)
        return True

    for c in node.get_children():
        if find_nested_structure_helper(c, location, history):
            if is_node_type_useful(node):
                history.append(node.location.line)
            return True

    return False

def find_nested_structure(node, location):
    history = []
    find_nested_structure_helper(node, location, history)
    history.reverse()
    return history


def find_nested_lines(fname, compilation_args, line_num):
    # TODO: check for errors
    index = clang.cindex.Index(clang.cindex.conf.lib.clang_createIndex(False, True))
    translation_unit = index.parse(fname, compilation_args)
    f = clang.cindex.File.from_name(translation_unit, translation_unit.spelling)
    (node, location) = get_node_in_line(translation_unit, f, line_num)
    lines = find_nested_structure(translation_unit.cursor, location)
    print lines
    return lines


# example: python NestedStructure.py ../../../../../mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcases/CWE476_NULL_Pointer_Dereference/CWE476_NULL_Pointer_Dereference__wchar_t_72a.cpp "-I ../../../../../mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcasesupport/" 41
if __name__ == "__main__":
    fname = sys.argv[1]
    args = sys.argv[2].split()
    line_num = int(sys.argv[3])
    lines = find_nested_lines(fname, args, line_num)
    print lines