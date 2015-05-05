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


def convert_ln_to_topformflat(line_numbers, indices):
    """
    Arguments:
    line_numbers -- list of line numbers having warnings
    indices -- list of indices corresponding to the source file with no comments
    """
    if indices:
        maximum = max(indices, key=lambda x: x[1])[1]
        maximum = max(max(line_numbers), maximum)

        is_index = _is_index_generator(indices, maximum)
        res = list(set([is_index[i-1] for i in line_numbers]))
        res.sort()
        return res
    else:
        return line_numbers


def convert_ln_to_original(flatten_indices, indices):
    """
    Arguments:
    flatten_indices -- indices of the topformflat to convert to source file
    indices -- indices describing the topformflat file
    """
    if indices and flatten_indices:
        res = []
        maximum = max(indices, key=lambda x: x[1])[1]
        maximum = max(max(flatten_indices), maximum)

        is_index = _is_index_generator(indices, maximum)
        for index in flatten_indices:
            for i in range(len(is_index)):
                if index == is_index[i]:
                    res.append(i + 1)
                # elif index < is_index[i]:
                #     break
        return res
    else:
        return flatten_indices
