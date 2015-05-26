#! /usr/bin/env python

class ND:

    # Test outcomes.
    PASS       = "PASS"
    FAIL       = "FAIL"
    UNRESOLVED = "UNRESOLVED"

    def __init__(self):
        self.test_result = self.UNRESOLVED
    #     self.outcome_cache  = OutcomeCache()
    #     self.cache_outcomes = 1

    # def _test(self, c):
    #     raise Exception("This method should be overloaded")

    # def test(self, c):
    #     # TODO: of course it doesn't cache at all!!!
    #     # if self.cache_outcomes:
    #     #     cached_result = self.outcome_cache.lookup(c)
    #     #     if cached_result != None:
    #     #         return cached_result
    #     return self._test(c)

    def __complements(self, c, size):
        """Return all the set complements of size size of c
        e.x.: complements([0,1,3,4,5], 2) = [[0,1,3], [1,3,4], [3,4,5]]
        """
        return  [c[:i] + c[i+size:] \
                        for i in list(range(len(c))) if i+size <= len(c)]

    def set_test_result(self, result):
        """Sets the test result for the last iteration of the minimize
        algorithm. 

        This is to be set every time minimize generates a set.
        """
        self.test_result = result

    def minimize(self, c, bound = 30, increase_size = False):
        """Algorithm to minimize the set c, by means of a Naive Debugging
        algorithm. After getting a result, you should set the test result in
        order to continue processing.

        Arguments:
        c -- set to minimize
        bound -- size of the set to start from (default: None)
        increase_size -- Start from the empty set and increase (default: False)
        """
        # assert self.test([]) == self.PASS
        # assert self.test(c) == self.FAIL

        if increase_size:
            if bound:
                rang = lambda x, y: list(range(min(y,x+1)), max(y,x+1)) + \
                                    list(range(1, min(y,x + 1)))
            else:
                rang = lambda x, y: list(range(1, x + 1))
        else:
            if bound:
                rang = lambda x, y: list(range(min(y,x), 0, -1)) + \
                                    list(range(max(x,y), y, -1))
            else:
                rang = lambda x, y: list(range(x, 0, -1))
        sth_changed = True

        last_num = bound

        while (sth_changed):
            sth_changed = False
            for i in rang(len(c), last_num):
                cs = self.__complements(c, i)
                for cc in cs:
                    yield cc
                    if self.test_result == self.FAIL:
                        c = cc
                        sth_changed = True
                        last_num = i
                        break
                if sth_changed:
                    break
        yield c


if __name__ == "__main__":
    nd = ND()
    c = [1,2,3,4,7,8,9,10,11,12,200]
    res = False
    code_snippets = nd.minimize(c, None, True)
    for c in code_snippets:
        print (c)
        if 2 in c and 3 in c and 7 in c:
            nd.set_test_result (nd.FAIL)
        else:
            nd.set_test_result (nd.PASS)

