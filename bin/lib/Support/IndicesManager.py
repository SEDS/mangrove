def convert_ln_to_no_comments(line_numbers, indices):
    """
    Arguments:
    line_numbers -- list of line numbers having warnings
    indices -- list of indices corresponding to the source file with no comments
    """
    res = []
    for ln in line_numbers:
        res.append(indices.index(ln) + 1)
    return res


def _is_index_generator(indices, maximum):
    is_index = [1] * (maximum + 1)
    for [fst, lst] in indices:
        for i in range(fst, lst):
            is_index[i] = 0
    for i in range(1, len(is_index)):
        is_index[i] += is_index[i-1]
    return is_index


# def convert_ln_to_topformflat(line_numbers, compressed_indices, indices):
#     """
#     Arguments:
#     line_numbers -- list of line numbers having warnings retalive to indices
#     compressed_indices -- list of indices corresponding to topformflat
#     indices -- list of indices being used in the original file
#     """
#     if compressed_indices:
#         # maximum = max(compressed_indices, key=lambda x: x[1])[1]
#         # maximum = max(max(line_numbers), maximum)

#         is_index = _is_index_generator(compressed_indices, len(indices))
#         res = list(set([is_index[i-1] for i in line_numbers]))
#         res.sort()
#         return res
#     else:
#         return [indices[i-1] for i in line_numbers]


def convert_ln_to_original(flatten_indices, compressed_indices, indices):
    """
    Arguments:
    flatten_indices -- indices of the topformflat to convert to source file
    compressed_indices -- indices describing the topformflat file
    indices -- list of indices corresponding to the original file
    """
    if compressed_indices and flatten_indices:
        # maximum = max(compressed_indices, key=lambda x: x[1])[1]
        # maximum = max(max(flatten_indices), maximum)

        tmp_ind = []
        is_index = _is_index_generator(compressed_indices, len(indices))
        for index in flatten_indices:
            for i in range(len(is_index)):
                if index == is_index[i]:
                    tmp_ind.append(i + 1)
                # elif index < is_index[i]:
                #     break
        # return [indices[i-1] for i in tmp_ind]
        return [indices[i-1] for i in tmp_ind if i <= len(indices)]
    else:
        return [indices[i-1] for i in flatten_indices]


if __name__ == "__main__":
    # assert convert_ln_to_topformflat([100], [[1,50],[52,100]], list(range(1,101))) == [3]
    # assert convert_ln_to_topformflat([3], [[1,2],[3,5]], [1,2,4,5,6,8,9,10]) == [2]
    # assert convert_ln_to_topformflat([7], [[1,2],[3,5]], [1,2,4,5,6,8,9,10]) == [4]
    # assert convert_ln_to_topformflat([7], [], [1,2,4,5,6,8,9,10]) == [9]
    # assert [8] == convert_ln_to_topformflat([13], [[6, 23], [25, 40]], [1, 2, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 147])

    assert convert_ln_to_original([2,3,6,8], [[1,2],[4,6]], [7,8,9,11,13,17,18,19,23,24,25,26]) == [9,11,13,17,23,25]
    assert convert_ln_to_original([], [[1,2],[4,6]], [7,8,9,11,13,17,18,19,23,24,25,26]) == []
    assert convert_ln_to_original([2,3,6,8], [], [7,8,9,11,13,17,18,19,23,24,25,26]) == [8,9,17,19]


