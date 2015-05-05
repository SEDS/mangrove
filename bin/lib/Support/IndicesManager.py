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


class IndexConverter:
    """As we are using several files, we have to convert the
    line numbers of the original file with the one with
    no comments and the flatten ones
    """
    def __init__(self, original_file_size, line_numbers_warns):
        self.original_size = original_file_size
        self.original_ln_warns = line_numbers_warns[:]
        self.no_comments_ln_warns = None
        self.flattened_lines = None
        self.flatten_minimized_ln = None

    def get_original_lines_warns(self):
        return self.original_ln_warns

    def calc_no_comments_ln_warns(self, no_comments_ln):
        self.no_comments_ln_warns = []
        for line in self.original_ln_warns:
            try:
                pos = no_comments_ln.index(line)
                self.no_comments_ln_warns.append(pos + 1)
            except ValueError:
                pass
        return self.no_comments_ln_warns

    def get_original_to_flatten_ln_warns(self, flattened_lines):
        assert self.no_comments_ln_warns is not None
        self.flattened_lines = flattened_lines
        if flattened_lines:
            is_index = [1] * self.original_size
            for [fst, lst] in flattened_lines:
                for i in range(fst, lst):
                    is_index[i] = 0
            for i in range(1, len(is_index)):
                is_index[i] += is_index[i-1]
            res = list(set([is_index[i-1] for i in self.no_comments_ln_warns]))
            res.sort()
            return res
        else:
            return self.no_comments_ln_warns

    def get_flatten_minimized_ln(self, dd_results):
        assert self.flattened_lines is not None
        if self.flattened_lines:
            is_index = [1] * self.original_size
            for [fst, lst] in self.flattened_lines:
                for i in range(fst, lst):
                    is_index[i] = 0
            for i in range(1, len(is_index)):
                is_index[i] += is_index[i-1]
            res = []
            for i in dd_results:
                for j in range(len(is_index)):
                    if i + 1 == is_index[j]:
                        res.append(j+1)
            self.flatten_minimized_ln = res
        else:
            self.flatten_minimized_ln = dd_results[:]
        return self.flatten_minimized_ln

    def get_flatten_to_no_comments_ln(self):
        res = []
        for num in self.no_comments_ln_warns:
            res.append(self.flatten_minimized_ln.index(num) + 1)
        self.no_comments_ln_warns = res
        return res
